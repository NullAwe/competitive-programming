#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<set<int>> keep;
vector<int> arr, dp, nr;
int ans;

bool dfs(int v, int p) {
  if (nr[v] >= 0) return nr[v];
  keep[v].insert(arr[v]);
  for (int u : adj[v]) {
    if (u == p || !dfs(u, v)) continue;
    if (keep[u].size() > keep[v].size()) swap(keep[u], keep[v]), swap(dp[u], dp[v]), dp[v] ^= arr[v], dp[u] ^= arr[v];
    for (int num : keep[u]) if (nr[v] < 0 && keep[v].count(num ^ dp[u] ^ dp[v])) ++ans, nr[v] = 0;
    for (int num : keep[u]) keep[v].insert(num ^ arr[v] ^ dp[u] ^ dp[v]);
  }
  if (!nr[v]) {
    dp[v] = 0, keep[v].clear();
    return nr[v];
  }
  return nr[v] = 1;
}

int main() {
  int n; cin >> n;
  arr.resize(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  adj.resize(n); for (int i = 0; i < n - 1; ++i) { int a, b; cin >> a >> b; --a, --b; adj[a].push_back(b), adj[b].push_back(a); }
  keep.resize(n), dp.resize(n), nr = vector<int>(n, -1), ans = 0;
  dfs(0, -1);
  cout << ans << '\n';
  return 0;
}
