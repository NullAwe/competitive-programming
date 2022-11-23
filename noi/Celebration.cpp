#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int MAX_N = 300001;

int n, m, q, k;
vector<int> iadj[MAX_N], irev[MAX_N], adj[MAX_N];
int gs[MAX_N], pre[MAX_N], lvl[MAX_N], bot[MAX_N];;
bool vis[MAX_N];

struct DSU {

  int r[MAX_N], p[MAX_N];

  DSU() { for (int i = 0; i < MAX_N; ++i) r[i] = 0, p[i] = i; }

  inline int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

  inline void link(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (r[a] < r[b]) swap(a, b);
    if (r[a] == r[b]) ++r[a];
    p[b] = a;
  }
};

DSU dsu;

struct MN {

  vector<pii> mns[22];
  vector<int> pos, lg;

  MN() {}

  MN(vector<pii>& a) : pos(n, -1), lg(a.size() + 1) {
    for (int i = 0; i < a.size(); ++i) if (pos[a[i].second] < 0) pos[a[i].second] = i;
    for (int i = 0; i < 22; ++i) mns[i].resize(a.size());
    for (int i = 0; i < a.size(); ++i) mns[0][i] = a[i];
    for (int i = 1; i < 22; ++i) for (int j = 0; j < a.size(); ++j) {
      pii x = mns[i - 1][j], y = mns[i - 1][min((int) a.size() - 1, j + (1 << (i - 1)))];
      mns[i][j] = x.first < y.first ? x : y;
    }
    lg[1] = 0;
    for (int i = 2; i <= a.size(); ++i) lg[i] = lg[i >> 1] + 1;
  }

  inline int query(int a, int b) {
    a = pos[dsu.find(a)], b = pos[dsu.find(b)];
    if (a > b) swap(a, b);
    int len = b - a + 1, dist = lg[len];
    pii x = mns[dist][a], y = mns[dist][b - (1 << dist) + 1];
    return x.first < y.first ? x.second : y.second;
  }
};

struct HLD {

  vector<pii> sparse;
  MN mn;

  inline int dfs1(int v, int p) {
    if (vis[v]) return bot[v];
    vis[v] = true, bot[v] = 0;
    for (int u : adj[v]) if (u != p) bot[v] = max(bot[v], dfs1(u, v) + 1);
    return bot[v];
  }

  inline void dfs2(int v, int p, int l) {
    vis[v] = true, lvl[v] = l;
    vector<pair<int, int>> us;
    for (int u : adj[v]) if (u != p) us.push_back({bot[u], u});
    sort(us.begin(), us.end()), reverse(us.begin(), us.end());
    vector<int> nadj;
    for (pair<int, int> u : us) if (!vis[u.second]) nadj.push_back(u.second), dfs2(u.second, v, l + 1);
    adj[v] = nadj;
  }

  inline void dfs3(int v, int p) {
    pre[v] = pre[p] + gs[v];
    sparse.push_back({lvl[v], v});
    for (int u : adj[v]) dfs3(u, v), sparse.push_back({lvl[v], v});
  }

  inline void init() {
    vector<bool> done(n);
    for (int i = 0; i < n; ++i) for (int u : adj[i]) done[u] = true, vis[i] = false;
    int v; for (v = 0; v < n; ++v) if (dsu.find(v) == v && !done[v]) break;
    dfs1(v, v);
    for (int i = 0; i < n; ++i) pre[i] = lvl[i] = vis[i] = 0;
    sparse.reserve(2 * m + 1), dfs2(v, v, 0), dfs3(v, v), mn = MN(sparse);
  }

  inline int query(int a, int b) { return mn.query(a, b) == a ? pre[b] - pre[a] + gs[a] : 0; }
};

HLD hld;

vector<int> order, comp;

inline void dfs1(int v) {
  vis[v] = true;
  for (int u : iadj[v]) if (!vis[u]) dfs1(u);
  order.push_back(v);
}

inline void dfs2(int v) {
  vis[v] = true, comp.push_back(v);
  for (int u : irev[v]) if (!vis[u]) dfs2(u);
}

inline void init() {
  order.reserve(n);
  for (int i = 0; i < n; ++i) vis[i] = false;
  for (int i = 0; i < n; ++i) if (!vis[i]) dfs1(i);
  reverse(order.begin(), order.end());
  for (int i = 0; i < n; ++i) vis[i] = false;
  for (int i : order) {
    if (vis[i]) continue;
    comp.clear(), dfs2(i);
    for (int v : comp) dsu.link(v, comp[0]);
  }
  for (int i = 0; i < n; ++i) for (int u : iadj[i]) if (dsu.find(i) != dsu.find(u)) adj[dsu.find(i)].push_back(dsu.find(u));
  for (int i = 0; i < MAX_N; ++i) gs[i] = 0;
  for (int i = 0; i < n; ++i) ++gs[dsu.find(i)];
}

int sz = 0, ans = 0;
vector<bool> vis1(21), vis2(21), here;
vector<int> info(6), nodes(21);

inline void dfs3(int v) {
  vis1[v] = true;
  for (int u = 0; u < sz; ++u)
    if (!vis1[u] && ((nodes[v] == info[2] && nodes[u] == info[3]) ||
        (nodes[v] == info[4] && nodes[u] == info[5]) || hld.mn.query(nodes[v], nodes[u]) == nodes[v])) dfs3(u);
}

inline void dfs4(int v) {
  vis2[v] = true;
  if (!vis1[v] || here[nodes[v]]) return;
  here[nodes[v]] = true;
  int mn = INT_MAX;
  for (int u = 0; u < sz; ++u) {
    int val = hld.mn.query(nodes[u], nodes[v]) == nodes[u] ? pre[nodes[v]] - pre[nodes[u]] + gs[nodes[u]] : 0;
    if (vis1[u] && val > gs[nodes[v]]) mn = min(mn, val - gs[nodes[u]]);
    if (!vis2[u] && ((nodes[v] == info[3] && nodes[u] == info[2]) ||
        (nodes[v] == info[5] && nodes[u] == info[4]) || val)) dfs4(u);
  }
  ans += mn == INT_MAX ? gs[nodes[v]] : mn;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m >> q >> k;
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    iadj[a].push_back(b), irev[b].push_back(a);
  }
  init(), hld.init();
  here.resize(n);
  for (int i = 0; i < q; ++i) {
    info.assign(6, 0);
    for (int j = 0; j <= k; ++j) {
      int a = 2 * j, b = a + 1;
      cin >> info[a] >> info[b]; --info[a], --info[b];
    }
    for (int j = 0; j < 6; ++j) info[j] = dsu.find(info[j]);
    sz = 0;
    for (int j = 0; j < 6; ++j) nodes[sz++] = info[j];
    for (int j = 0; j < 6; ++j) {
      for (int l = j + 1; l < 6; ++l) {
        bool add = true;
        int lca = hld.mn.query(info[j], info[l]);
        for (int m = 0; m < sz; ++m) if (lca == nodes[m]) add = false;
        if (add) nodes[sz++] = hld.mn.query(info[j], info[l]);
      }
    }
    vis1.assign(sz, false), vis2.assign(sz, false), dfs3(0), dfs4(1);
    for (int v = 0; v < sz; ++v) here[nodes[v]] = false;
    cout << ans << '\n';
    ans = 0;
  }
  return 0;
}
