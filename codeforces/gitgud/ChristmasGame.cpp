#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

int n, k;
vector<vector<pii>> adj;
vector<pii> edges;
vector<int> arr, miss;
vector<vector<int>> memo, xors;

inline void dp(int v) {
  if (memo[v][0] >= 0) return;
  if (miss[edges[v].second] < 0) {
    for (pii u : adj[edges[v].second]) if (u.first != edges[v].first) dp(u.second);
  } else if (miss[edges[v].second] < INT_MAX) {
    dp(miss[edges[v].second]);
  }
  for (int x = 0; x < 2 * k; ++x) {
    memo[v][x] = (x >= k) * arr[edges[v].second];
    if (miss[edges[v].second] < 0) {
      for (pii u : adj[edges[v].second]) if (u.first != edges[v].first) xors[edges[v].second][x] ^= memo[u.second][(x + 1) % (2 * k)];
      memo[v][x] ^= xors[edges[v].second][x];
    } else if (miss[edges[v].second] < INT_MAX) {
      xors[edges[v].second][x] ^= memo[miss[edges[v].second]][(x + 1) % (2 * k)];
    }
    if (miss[edges[v].second] >= 0) memo[v][x] ^= xors[edges[v].second][x] ^ memo[v ^ 1][(x + 1) % (2 * k)];
  }
  if (miss[edges[v].second] < 0) miss[edges[v].second] = v ^ 1;
  else miss[edges[v].second] = INT_MAX;
}

int main() {
  cin >> n >> k;
  adj.resize(n), edges.resize(2 * n - 2), arr.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back({b, 2 * i});
    adj[b].push_back({a, 2 * i + 1});
    edges[2 * i] = {a, b};
    edges[2 * i + 1] = {b, a};
  }
  for (int i = 0; i < n; ++i) cin >> arr[i];
  miss = vector<int>(2 * n - 2, -1);
  xors = vector<vector<int>>(n, vector<int>(2 * k));
  memo = vector<vector<int>>(2 * n - 2, vector<int>(2 * k, -1));
  for (int i = 0; i < 2 * n - 2; ++i) if (memo[i][0] < 0) dp(i);
  for (int v = 0; v < n; ++v) {
    int ans = 0;
    for (pii u : adj[v]) ans ^= memo[u.second][1];
    cout << (ans > 0) << ' ';
  }
  cout << '\n';
  return 0;
}
