#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 1000000007;
 
int main() {
  int n, m;
  cin >> n >> m;
  --m;
  vector<int> desc(n);
  for (int i = 0; i < n; ++i) {
    cin >> desc[i];
    --desc[i];
  }
  vector<vector<int>> memo(n + 1, vector<int>(m + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (desc[i - 1] >= 0 && j != desc[i - 1]) continue;
      if (j == 0 && j == m) memo[i][j] = memo[i - 1][j];
      else if (j == 0) memo[i][j] = (memo[i - 1][j] + memo[i - 1][j + 1]) % MOD;
      else if (j == m) memo[i][j] = (memo[i - 1][j - 1] + memo[i - 1][j]) % MOD;
      else {
        memo[i][j] = (memo[i - 1][j] + memo[i - 1][j + 1]) % MOD;
        memo[i][j] = (memo[i][j] + memo[i - 1][j - 1]) % MOD;
      }
      if (i == 1) ++memo[i][j];
    }
  }
  int sum = 0;
  for (int num : memo[n]) sum = (sum + num) % MOD;
  cout << sum << "\n";
  return 0;
}
