#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

vector<int> parent, order, maxK;

int setOrder(int node, int p, vector<vector<int>>& adj) {
  parent[node] = p;
  order.push_back(node);
  for (int next : adj[node]) if (next != p) maxK[node] = max(maxK[node], setOrder(next, node, adj) + 1);
  return maxK[node];
}

int main() {
  int n, k; cin >> n >> k;
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  if (!k) {
    cout << "1\n";
    return 0;
  }
  parent = vector<int>(n); order.reserve(n); maxK = vector<int>(n); setOrder(0, -1, adj);
  reverse(order.begin(), order.end());
  vector<vector<int>> dp(n, vector<int>(k + 1));
  vector<int> sums(n);
  for (int node : order) {
    dp[node][0] = 1;
    int curDepth = 0;
    for (int next : adj[node]) {
      if (next == parent[node]) continue;
      for (int total = k; total > 0; --total) {
        int nv = (int) ((ll) dp[node][total] * sums[next] % MOD);
        if (total - 1 <= maxK[next])
          for (int rest = 0; rest + total <= k && rest <= min(total, curDepth); ++rest)
            nv = (nv + (int) ((ll) dp[next][total - 1] * dp[node][rest] % MOD)) % MOD;
        if (total <= curDepth)
          for (int nc = 0; nc < min(total - 1, maxK[next] + 1) && total + nc + 1 <= k; ++nc)
            nv = (nv + (int) ((ll) dp[next][nc] * dp[node][total] % MOD)) % MOD;
        dp[node][total] = nv;
      }
      curDepth = max(curDepth, maxK[next] + 1);
      dp[node][0] = (int) ((ll) dp[node][0] * sums[next] % MOD);
    }
    for (int i = 0; i <= k; ++i) sums[node] = (sums[node] + dp[node][i]) % MOD;
  }
  int ans = 0;
  for (int i = 0; i <= k; ++i) ans = (ans + dp[0][i]) % MOD;
  cout << ans << '\n';
}
