#include <bits/stdc++.h>
using namespace std;

using ll = long;
 
const ll oo = 2147483647;
const ll mod = 1000000007;
 
int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    adj[b].push_back(a);
  }
  int sz = 1 << n;
  vector<vector<ll>> memo(sz, vector<ll>(n));
  memo[1][0] = 1;
  for (int i = 1; i < sz; ++i) {
    for (int j = 0; j < n; ++j) {
      if (!(i & (1 << j)) || memo[i][j]) continue;
      int nxt = i & ~(1 << j);
      for (int num : adj[j]) {
        if (!memo[nxt][num]) continue;
        memo[i][j] = (memo[i][j] + memo[nxt][num]) % mod;
      }
    }
  }
  cout << memo[sz - 1][n - 1];
  return 0;
}
