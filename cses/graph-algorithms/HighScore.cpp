#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const ll N_INF = -1e18;

int main() {
  int n, m; cin >> n >> m;
  vector<pair<pii, ll>> edges(m);
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    edges[i] = {{a, b}, w};
  }
  vector<ll> d(n, N_INF); d[0] = 0;
  for (int i = 0; i < n - 1; ++i)
    for (pair<pii, ll> p : edges)
      if (d[p.first.first] > N_INF) d[p.first.second] = max(d[p.first.second], d[p.first.first] + p.second);
  vector<ll> o = d;
  for (pair<pii, ll> p : edges)
    if (d[p.first.first] > N_INF) d[p.first.second] = max(d[p.first.second], d[p.first.first] + p.second);
  if (o == d) {
    cout << d[n - 1] << '\n';
    return 0;
  }
  vector<bool> vis(n);
  queue<int> q;
  for (int i = 0; i < n; ++i) if (d[i] != o[i]) vis[i] = true, q.push(i);
  while (q.size()) {
    int node = q.front(); q.pop();
    for (pair<pii, ll> p : edges) {
      if (p.first.first != node || vis[p.first.second]) continue;
      vis[p.first.second] = true, q.push(p.first.second);
    }
  }
  cout << (vis[n - 1] ? -1 : d[n - 1]) << '\n';
  return 0;
}
