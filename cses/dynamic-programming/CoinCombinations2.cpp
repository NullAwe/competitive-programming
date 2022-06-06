#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
int main() {
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int i = 0; i < n; ++i) cin >> coins[i];
  vector<vector<int>> memo(n + 1, vector<int>(x + 1));
  memo[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= x; ++j) {
      memo[i][j] = memo[i - 1][j];
      int l = j - coins[i - 1];
      if (l >= 0) memo[i][j] = (memo[i][j] + memo[i][l]) % 1000000007;
    }
  }
  cout << memo[n][x] << "\n";
  return 0;
}
