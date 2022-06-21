#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MAX_N = 200001;

vector<int> adj[MAX_N];
bool used[MAX_N];
int parent[MAX_N], sizes[MAX_N], level[MAX_N], n, a, b, ml = 0;
ll t[MAX_N];
vector<int> group;

inline void add(int p, int delta) {
  for (; p < n; p = p | (p + 1)) t[p] += delta;
}

inline ll sum(int r) {
  if (r < 0) return 0;
  ll ans = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1) ans += t[r];
  return ans;
}

inline pii centroid(int r) {
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
    if (m <= order.size() / 2) return {v, order.size()};
  }
  return {-1, -1};
}

inline void dfs(int v, int p, int l) {
  group.push_back(v), level[v] = l, ml = max(ml, l);
  for (int u : adj[v]) if (!used[u] && u != p) dfs(u, v, l + 1);
}

inline ll solve(int v) {
  ll ans = 0;
  pii info = centroid(v);
  v = info.first;
  for (int i = 0; i < info.second; ++i) t[i] = 0;
  add(0, 1);
  for (int u : adj[v]) {
    if (used[u]) continue;
    dfs(u, v, 1);
    vector<int> srm(ml + 1);
    for (int node : group) ++srm[level[node]];
    for (int l = 0; l <= min(ml, b); ++l) ans += (ll) srm[l] * (sum(min(b - l, info.second - 1)) - sum(min(a - 1 - l, info.second - 1)));
    for (int node : group) add(level[node], 1);
    group.resize(0), ml = 0;
  }
  used[v] = true;
  for (int u : adj[v]) if (!used[u]) ans += solve(u);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> a >> b;
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  group.reserve(n);
  for (int i = 0; i < MAX_N; ++i) used[i] = parent[i] = sizes[i] = level[i] = t[i] = 0;
  add(0, 1);
  cout << solve(0) << '\n';
  return 0;
}

