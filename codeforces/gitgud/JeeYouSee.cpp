#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

int main() {
  int n; cin >> n;
  vector<vector<int>> nCr(n + 1, vector<int>(n + 1));
  for (int i = 0; i <= n; ++i) nCr[i][0] = nCr[i][i] = 1;
  for (int i = 2; i <= n; ++i) for (int j = 1; j < i; ++j) nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]) % MOD;
  ll l, r, z; cin >> l >> r >> z;
  if (z > r) {
    cout << 0 << '\n';
    return 0;
  }
  vector<int> dp(2 * n + 1, 1);
  for (int i = 0; i < 63; ++i) {
    vector<int> ndp(2 * n + 1);
    int p = (z >> i) & 1, p2 = (r >> i) & 1;
    for (int has = 0; has <= 2 * n; ++has) {
      for (int use = p; use <= min(has + p2, n); use += 2) {
        ndp[has] = (ndp[has] + (int) ((ll) dp[2 * min(has - use + p2, n)] * nCr[n][use] % MOD)) % MOD;
      }
    }
    dp = ndp;
  }
  int sum = dp[0];
  if (z >= l) {
    cout << sum << '\n';
    return 0;
  }
  dp = vector<int>(2 * n + 1, 1);
  for (int i = 0; i < 63; ++i) {
    vector<int> ndp(2 * n + 1);
    int p = (z >> i) & 1, p2 = ((l - 1) >> i) & 1;
    for (int has = 0; has <= 2 * n; ++has) {
      for (int use = p; use <= min(has + p2, n); use += 2) {
        ndp[has] = (ndp[has] + (int) ((ll) dp[2 * min(has - use + p2, n)] * nCr[n][use] % MOD)) % MOD;
      }
    }
    dp = ndp;
  }
  cout << (sum + MOD - dp[0]) % MOD << '\n';
  return 0;
}
