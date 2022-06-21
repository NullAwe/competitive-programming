#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<vector<int>> adj;
vector<bool> used;
vector<int> parent, sizes, level, group;
int n, k, ml = 0;

inline int centroid(int r) {
  vector<int> order;
  queue<pii> q; q.push({r, r});
  while (q.size()) {
    pii front = q.front(); q.pop();
    int v = front.first, p = front.second;
    order.push_back(v), parent[v] = p;
    for (int u : adj[v]) if (!used[u] && u != p) q.push({u, v});
  }
  for (int v : order) sizes[v] = 1;
  for (int i = order.size() - 1; i > 0; --i) sizes[parent[order[i]]] += sizes[order[i]];
  for (int v : order) {
    int m = sizes[r] - sizes[v];
    for (int u : adj[v]) if (!used[u] && u != parent[v]) m = max(m, sizes[u]);
    if (m <= order.size() / 2) return v;
  }
  return -1;
}

inline void dfs(int v, int p, int l) {
  group.push_back(v), level[v] = l, ml = max(ml, l);
  for (int u : adj[v]) if (!used[u] && u != p) dfs(u, v, l + 1);
}

inline ll solve(int v) {
  ll ans = 0;
  v = centroid(v);
  vector<int> m(1, 1);
  for (int u : adj[v]) {
    if (used[u]) continue;
    dfs(u, v, 1);
    vector<int> srm(ml + 1);
    for (int node : group) ++srm[level[node]];
    for (int l = max(k - (int) m.size() + 1, 0); l <= min(ml, k); ++l) ans += (ll) srm[l] * m[k - l];
    if (ml >= m.size()) m.resize(ml + 1);
    for (int node : group) ++m[level[node]];
    group.clear(), ml = 0;
  }
  used[v] = true;
  for (int u : adj[v]) if (!used[u]) ans += solve(u);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> k;
  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  used.resize(n), parent.resize(n), sizes.resize(n), level.resize(n);
  cout << solve(0) << '\n';
  return 0;
}

