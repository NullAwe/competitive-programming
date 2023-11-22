#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MOD = 1e9 + 7;
const int LG = 20;

struct Node;

int n, m;
vector<vector<int>> adj, up;
map<pii, string> ma;
vector<Node*> nodes;
vector<int> inds;
vector<set<int>> ba;

struct Node {

  int dig, dep, idx, pa;
  ll val;
  vector<int> children;

  Node(int dig, int dep, int idx, int pa, ll vp) : dig(dig), dep(dep), idx(idx), pa(pa),
                                            val((10 * vp + max(dig, 0)) % MOD), children(10, -1) {
    vector<int> tup(LG); tup[0] = pa;
    if (up.size()) for (int i = 1; i < LG; ++i) tup[i] = up[tup[i - 1]][i - 1];
    up.push_back(tup);
  }

  int addChild(string s, int i) {
    if (i >= (int) s.size()) return idx;
    if (children[s[i] - '0'] < 0) {
      children[s[i] - '0'] = (int) nodes.size();
      nodes.push_back(new Node(s[i] - '0', dep + 1, children[s[i] - '0'], idx, val));
    }
    return nodes[children[s[i] - '0']]->addChild(s, i + 1);
  }

  bool operator<(const Node& rhs) const {
    if (dep != rhs.dep) return dep < rhs.dep;
    int x = idx, y = rhs.idx;
    for (int i = LG - 1; i >= 0; --i) if (up[x][i] != up[y][i]) x = up[x][i], y = up[y][i];
    return nodes[x]->dig < nodes[y]->dig;
  }
};

bool cmp(Node* a, Node* b){
  return *a < *b;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m;
  adj.resize(n), inds.resize(n), ba.resize(1000000);
  for (int i = 0; i < m; ++i) {
    int x, y; cin >> x >> y; --x, --y;
    adj[x].push_back(y), adj[y].push_back(x);
    ma[{x, y}] = ma[{y, x}] = to_string(i + 1);
  }
  nodes.push_back(new Node(-1, 0, 0, 0, 0));
  vector<bool> done(n);
  vector<bool> vis(n); vis[0] = true;
  multiset<Node*, decltype(cmp)*> s(cmp);
  s.insert(nodes[0]);
  inds[0] = 0;
  ba[0].insert(0);
  while (s.size()) {
    Node* top = *s.begin(); s.erase(s.begin());
    int v = *ba[top->idx].begin();
    done[v] = true;
    for (int u : adj[v]) {
      if (done[u]) continue;
      string id = ma[{v, u}];
      int nn = top->addChild(id, 0);
      if (!vis[u]) {
        vis[u] = true;
        inds[u] = nn, ba[nn].insert(u);
        s.insert(nodes[nn]);
      }
      if (cmp(nodes[nn], nodes[inds[u]])) {
        ba[inds[u]].erase(u);
        s.erase(s.find(nodes[inds[u]]));
        s.insert(nodes[inds[u] = nn]);
        ba[nn].insert(u);
      }
    }
    ba[top->idx].erase(v);
  }
  for (int i = 1; i < n; ++i) cout << nodes[inds[i]]->val << '\n';
  return 0;
}