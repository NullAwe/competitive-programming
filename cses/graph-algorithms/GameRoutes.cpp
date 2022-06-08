#include <bits/stdc++.h>
using namespace std;
 
int dp(vector<vector<int>> &adj, vector<int> &memo, int node) {
  if (memo[node] != 0) return memo[node];
  for (int next : adj[node]) {
    int num = dp(adj, memo, next);
    if (num <= 0) continue;
    memo[node] += num;
    memo[node] %= 1000000007;
  }
  if (memo[node] == 0) memo[node] = -1;
  return memo[node];
}
 
int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    adj[a].push_back(b);
  }
  vector<int> memo(n);
  memo[n - 1] = 1;
  for (int i = 0; i < n; ++i) dp(adj, memo, i);
  if (memo[0] <= 0) {
    cout << "0\n";
    return 0;
  }
  cout << memo[0] << "\n";
  return 0;
}
