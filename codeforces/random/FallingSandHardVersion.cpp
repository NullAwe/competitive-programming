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

vector<set<int>> nrev;
vector<pii> rngs;

void dfs3(int v) {
  if (dsu.find(v) != v || vis[v]) return;
  vis[v] = true;
  for (int u : nrev[v]) {
    dfs3(u);
    rngs[v].first = min(rngs[v].first, rngs[u].first);
    rngs[v].second = max(rngs[v].second, rngs[u].second);
  }
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
  nrev.resize(n * m);
  for (int i = 0; i < n * m; ++i) {
    for (int u : adj[i]) {
      int pi = dsu.find(i), pu = dsu.find(u);
      if (pi == pu) continue;
      nrev[pu].insert(pi);
    }
  }
  rngs.resize(n * m);
  for (int i = 0; i < n * m; ++i) rngs[i] = {i % m, i % m};
  for (int i = 0; i < n * m; ++i) {
    int y = i % m;
    int pi = dsu.find(i);
    rngs[pi].first = min(rngs[pi].first, y);
    rngs[pi].second = max(rngs[pi].second, y);
  }
  vis.assign(n * m, false);
  for (int i = 0; i < n * m; ++i) dfs3(i);
  for (int i = 0; i < n * m; ++i) if (dsu.find(i) != i) rngs[i] = rngs[dsu.find(i)];
}

int main() {
  cin >> n >> m;
  vector<string> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> counts(m); for (int i = 0; i < m; ++i) cin >> counts[i];
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
  pii rng = {-1, -1};
  for (int i = 0; i < m; ++i) {
    if (counts[i] == 0) continue;
    int ind, count = 0;
    for (ind = n - 1; ind >= 0; --ind) {
      if (arr[ind][i] == '#') ++count;
      if (count == counts[i]) break;
    }
    pii comb = rngs[ind * m + i], _try;
    _try.first = max(rng.first, comb.first);
    _try.second = min(rng.second, comb.second);
    if (_try.first > _try.second) ++ans, rng = comb;
    else rng = _try;
  }
  cout << ans << '\n';
  return 0;
}