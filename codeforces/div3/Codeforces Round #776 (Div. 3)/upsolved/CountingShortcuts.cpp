#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

void solve() {
  int n, m, s, t; cin >> n >> m >> s >> t; --s; --t;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<ll> dists(n, -1), ways(n); dists[s] = 0, ways[s] = 1;
  queue<int> q; q.push(s);
  while (q.size()) {
    int node = q.front(); q.pop();
    for (int next : adj[node]) {
      if (dists[next] == dists[node] + 1) ways[next] = (ways[next] + ways[node]) % MOD;
      if (dists[next] >= 0) continue;
      dists[next] = dists[node] + 1, ways[next] = ways[node];
      q.push(next);
    }
  }
  ll ans = ways[t];
  vector<ll> waymore(n);
  vector<bool> visited(n); visited[s] = true;
  q.push(s);
  while (q.size()) {
    int node = q.front(); q.pop();
    for (int next : adj[node]) {
      if (dists[next] == dists[node]) waymore[node] = (waymore[node] + ways[next]) % MOD;
      if (dists[next] == dists[node] - 1) waymore[node] = (waymore[node] + waymore[next]) % MOD;
      if (visited[next]) continue;
      visited[next] = true;
      q.push(next);
    }
  }
  cout << (ways[t] + waymore[t]) % MOD << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
