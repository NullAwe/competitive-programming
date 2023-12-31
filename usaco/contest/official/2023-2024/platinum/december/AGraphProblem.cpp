#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define ll long long

const int MOD = 1e9 + 7;

vector<ll> p10;

struct DSU {

  vector<int> r, p;

  DSU(int n) : r(n, 1), p(n) {
    for (int i = 0; i < n; ++i) p[i] = i;
  }

  int find(int a) {
    return a == p[a] ? a : p[a] = find(p[a]);
  }

  bool same_set(int a, int b) {
    return find(a) == find(b);
  }

  void link(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (r[a] < r[b]) swap(a, b);
    p[b] = a;
    r[a] += r[b];
  }
};

class Node {
  public:
    int sz, w, id;
    Node *l = nullptr, *r = nullptr;
    ll val;
    bool rev = 0;

    Node(int id) : id(id), sz(1), w(rand()), val(id) {}
};

int szof(Node* rt) {
  return rt ? rt->sz : 0;
}

void prop(Node* rt) {
	if (!rt->rev) return;
	if (rt->l) rt->l->rev ^= 1;
	if (rt->r) rt->r->rev ^= 1;
	swap(rt->l, rt->r);
	rt->rev = 0;
}

void upd(Node* rt) {
	rt->sz = szof(rt->l) + szof(rt->r) + 1;
  if (rt->r) rt->val = ((ll) rt->id * p10[szof(rt->r)] % MOD + rt->r->val) % MOD;
  else rt->val = rt->id;
  if (rt->l) {
    rt->val = (rt->l->val * p10[szof(rt->r) + 1] % MOD + rt->val) % MOD;
  }
}

void split(Node* root, Node*& l, Node*& r, int idx) {
	if (!root) {
		l = r = nullptr;
		return;
	}
	prop(root);
	if (szof(root->l) + 1 <= idx) {
		split(root->r, root->r, r, idx - szof(root->l) - 1);
		l = root;
	} else {
		split(root->l, l, root->l, idx);
		r = root;
	}
	upd(root);
}

void merge(Node *&root, Node *l, Node *r) {
	if (!l && !r) {
		root = nullptr;
		return;
	}
	if (!l && r) {
		root = r;
		return;
	}
	if (l && !r) {
		root = l;
		return;
	}
	prop(l), prop(r);
	if (l->w > r->w) {
		merge(l->r, l->r, r);
		root = l;
	} else {
		merge(r->l, l, r->l);
		root = r;
	}
	upd(root);
}

ll get(Node *root, int pos) {
	prop(root);
	int rtpos = szof(root->l)+1;
	if (rtpos == pos) return root->val;
	if (rtpos < pos) return get(root->r, pos-rtpos);
	return get(root->l, pos);
}

vector<vector<pii>> adj;
vector<vector<pii>> info;

vector<ll> ans;
vector<int> loc;
Node* rt = nullptr;
int ps;

void dfs(int v, int p) {
  ll tans = ans[v];
  for (int i = 0; i < adj[v].size(); ++i) {
    pii pp = adj[v][i];
    assert(adj[v].size() == info[v].size());
    if (pp.second == p) continue;
    int aa = info[v][i].first, bb = info[v][i].second;
    if (aa == 0 && bb) {
      Node *r1 = nullptr, *r2 = nullptr;
      split(rt, rt, r1, bb + 1);
      split(rt, rt, r2, 1);
      merge(r2, r2, rt);
      merge(r2, r2, r1);
      rt = r2;
    } else if (bb == 0 && aa) {
      Node *r1 = nullptr, *r2 = nullptr;
      split(rt, rt, r1, aa + 1);
      split(rt, rt, r2, aa);
      merge(r2, r2, rt);
      merge(r2, r2, r1);
      rt = r2;
    } else if (aa) {
      Node *r1 = nullptr, *r2 = nullptr, *r3 = nullptr;
      split(rt, rt, r1, aa + bb + 1);
      split(rt, rt, r2, aa + 1);
      split(rt, rt, r3, aa);
      merge(r2, r2, r3);
      merge(r2, r2, rt);
      merge(r2, r2, r1);
      rt = r2;
    }
    ans[pp.second] = rt->val;
    dfs(pp.second, v);
    swap(aa, bb);
    Node *r1 = nullptr, *r2 = nullptr, *r3 = nullptr;
    split(rt, rt, r1, aa + bb + 1);
    split(rt, rt, r2, aa + 1);
    split(rt, rt, r3, aa);
    merge(r2, r2, r3);
    merge(r2, r2, rt);
    merge(r2, r2, r1);
    rt = r2;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  adj.resize(n);
  DSU dsu(n);
  vector<pii> vv;
  info.resize(n);
  for (int i = 1; i <= m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    vv.push_back({a, b});
    if (dsu.same_set(a, b)) continue;
    adj[a].push_back({i, b});
    adj[b].push_back({i, a});
    info[a].push_back({dsu.r[dsu.find(a)] - 1, dsu.r[dsu.find(b)] - 1});
    info[b].push_back({dsu.r[dsu.find(b)] - 1, dsu.r[dsu.find(a)] - 1});
    dsu.link(a, b);
  }
  p10.resize(n + 2);
  p10[0] = 1;
  for (int i = 1; i < n + 2; ++i) p10[i] = (p10[i - 1] * 10) % MOD;
  vector<bool> vis(n); vis[0] = true;
  vector<int> path;
  set<pii> edges; for (pii p : adj[0]) edges.insert(p);
  while (edges.size()) {
    pii beg = *edges.begin(); edges.erase(edges.begin());
    if (vis[beg.second]) continue;
    vis[beg.second] = true;
    path.push_back(beg.first);
    for (pii p : adj[beg.second]) edges.insert(p);
  }
  ll h = 0;
  for (int num : path) h = (10 * h + num) % MOD;
  ans.resize(n);
  ans[0] = h;
  ps = (int) path.size();
  loc.resize(m + 1, -1);
  for (int i = 0; i < ps; ++i) loc[path[i]] = i, merge(rt, rt, new Node(path[i]));
  dfs(0, 0);
  for (ll num : ans) cout << num << '\n';
  return 0;
}