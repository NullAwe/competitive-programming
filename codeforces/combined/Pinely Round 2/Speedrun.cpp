#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define pll pair<ll, ll>

inline void solve() {
  int n, m, d; cin >> n >> m >> d;
  vector<vector<int>> adj(n), rev(n);
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    rev[b].push_back(a);
  }
  vector<int> ind(n);
  for (int i = 0; i < n; ++i) for (int u : adj[i]) ++ind[u];
  queue<int> q; for (int i = 0; i < n; ++i) if (!ind[i]) q.push(i);
  vector<int> order;
  while (q.size()) {
    int v = q.front(); q.pop();
    order.push_back(v);
    for (int u : adj[v]) {
      --ind[u];
      if (!ind[u]) q.push(u);
    }
  }
  vector<ll> dist(n);
  reverse(order.begin(), order.end());
  for (int v : order) {
    if (adj[v].empty()) {
      dist[v] = arr[v];
      continue;
    }
    ll mn = LLONG_MAX;
    for (int u : adj[v]) mn = min(mn, dist[u]);
    dist[v] = mn - ((mn % d + d) % d) + arr[v];
    if (dist[v] > mn) dist[v] -= d;
  }
  vector<multiset<int>> ms(n);
  multiset<ll> dists;
  ll mx = dist[0], mn = dist[0];
  vector<pll> a2;
  for (int v = 0; v < n; ++v) {
    mx = max(mx, dist[v]), mn = min(mn, dist[v]), dists.insert(dist[v]);
    for (int u : adj[v]) ms[v].insert(dist[u]);
    if (adj[v].empty()) a2.push_back({dist[v], v});
  }
  sort(a2.begin(), a2.end());
  vector<bool> vis(n);
  for (pll pp : a2) {
    int v = pp.second;
    q.push(v);
    vis[v] = true;
    while (q.size()) {
      int v2 = q.front(); q.pop();
      dists.erase(dists.find(dist[v2]));
      dists.insert(dist[v2] + d);
      for (int u : rev[v2]) {
        ms[u].erase(ms[u].find(dist[v2]));
        ms[u].insert(dist[v2] + d);
        if (dist[u] + d <= *ms[u].begin()) {
          if (!vis[u]) q.push(u);
          vis[u] = true;
        }
      }
      dist[v2] += d;
    }
    if (*--dists.end() - *dists.begin() < mx - mn) {
      mn = *dists.begin(), mx = *--dists.end();
    }
  }
  cout << mx - mn << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
