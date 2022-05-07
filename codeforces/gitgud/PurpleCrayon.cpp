#include <bits/stdc++.h>
using namespace std;

#define ll long long

int32_t main() {
  int n, k; cin >> n >> k;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    adj[a].push_back(b); adj[b].push_back(a);
  }
  vector<int> depth(n, -1);
  vector<int> parent(n, -1);
  queue<int> q; q.push(0); depth[0] = 0;
  while (q.size()) {
    int node = q.front(); q.pop();
    for (int next : adj[node]) {
      if (depth[next] >= 0) {
        parent[node] = next;
        continue;
      }
      q.push(next); depth[next] = depth[node] + 1;
    }
  }
  vector<pair<int, int>> depths(n); for (int i = 0; i < n; ++i) depths[i] = {depth[i], i};
  sort(depths.begin(), depths.end());
  vector<int> val(n, 0);
  vector<bool> marked(n);
  for (int i = n - 1; i >= 0; --i) {
    int node = depths[i].second;
    while (node >= 0 && !marked[node]) {
      ++val[depths[i].second];
      marked[node] = true;
      node = parent[node];
    }
  }
  vector<pair<int, int>> vals(n); for (int i = 0; i < n; ++i) vals[i] = {val[i], i};
  sort(vals.begin(), vals.end());
  int av = n;
  ll ans = - (ll) (n - (n >> 1)) * (n >> 1);
  for (int i = 1; i <= k; ++i) {
    av -= vals[n - i].first;
    ans = max(ans, (ll) i * (n - i) - (ll) (n - min(av, n >> 1)) * min(av, n >> 1));
  }
  cout << ans << '\n';
}
