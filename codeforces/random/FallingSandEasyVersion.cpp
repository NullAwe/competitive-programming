#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

struct DSU {

  vector<int> r, p;

  DSU() {}

  DSU(int n) : r(n), p(n) {
    for (int i = 0; i < n; ++i) p[i] = i;
  }

  int find(int a) {
    return a == p[a] ? a : p[a] = find(p[a]);
  }

  void link(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (r[a] < r[b]) swap(a, b);
    if (r[a] == r[b]) ++r[a];
    p[b] = a;
  }
};

int n, m;

vector<vector<int>> adj, rev;
vector<int> in;

inline int get(int x, int y) {
  return x * m + y;
}

vector<int> order, comp;
vector<bool> vis;
DSU dsu;

void dfs(int v) {
  if (vis[v]) return;
  vis[v] = true;
  for (int u : adj[v]) dfs(u);
  order.push_back(v);
}

void dfs2(int v) {
  if (vis[v]) return;
  vis[v] = true;
  comp.push_back(v);
  for (int u : rev[v]) dfs2(u);
}

void complete() {
  in.resize(n * m);
  vis.resize(n * m);
  for (int i = 0; i < n * m; ++i) dfs(i);
  rev.resize(n * m);
  for (int i = 0; i < n * m; ++i) for (int u : adj[i]) rev[u].push_back(i);
  reverse(order.begin(), order.end());
  dsu = DSU(n * m);
  vis.assign(n * m, false);
  for (int v : order) {
    comp.clear();
    dfs2(v);
    for (int i = 1; i < comp.size(); ++i) dsu.link(comp[i], comp[i - 1]);
  }
  for (int i = 0; i < n * m; ++i) {
    for (int u : adj[i]) {
      int pi = dsu.find(i), pu = dsu.find(u);
      if (pi == pu) continue;
      ++in[pu];
    }
  }
}

int main() {
  cin >> n >> m;
  vector<string> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<set<int>> sets(m);
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (arr[i][j] == '#') sets[j].insert(i);
  adj.resize(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (arr[i][j] == '.') continue;
      auto it = sets[j].upper_bound(i);
      if (it != sets[j].end()) adj[get(i, j)].push_back(get(*it, j));
      if (i && arr[i - 1][j] == '#') adj[get(i, j)].push_back(get(i - 1, j));
      if (j) {
        it = sets[j - 1].lower_bound(i);
        if (it != sets[j - 1].end()) adj[get(i, j)].push_back(get(*it, j - 1));
      }
      if (j < m - 1) {
        it = sets[j + 1].lower_bound(i);
        if (it != sets[j + 1].end()) adj[get(i, j)].push_back(get(*it, j + 1));
      }
    }
  }
  complete();
  int ans = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    if (arr[i][j] == '#' && !in[get(i, j)] && (dsu.find(get(i, j)) == get(i, j))) ++ans;
  cout << ans << '\n';
  return 0;
}