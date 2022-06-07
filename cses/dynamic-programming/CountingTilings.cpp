#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
  int n, m; cin >> n >> m;
  vector<int> dp(1 << n); dp[0] = 1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      vector<int> ndp(1 << n);
      for (int k = 0; k < (1 << n); ++k) {
        ndp[k] = dp[k ^ (1 << j)];
        if (j && !(k & (1 << j)) && !(k & (1 << (j - 1)))) ndp[k] = (ndp[k] + dp[k ^ (1 << (j - 1))]) % MOD;
      }
      dp = ndp;
    }
  }
  cout << dp[0] << '\n';
  return 0;
}
