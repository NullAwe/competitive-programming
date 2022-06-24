#include <bits/stdc++.h>
using namespace std;

double solve(int x, int n) {
  vector<double> dp(6 * n + 1); dp[0] = 1;
  for (int i = 0; i < n; ++i) {
    vector<double> ndp(6 * n + 1);
    for (int j = 0; j <= 6 * n + 1; ++j) {
      for (int m = 1; m <= 6; ++m) {
        if (j - m < 0) break;
        ndp[j] += dp[j - m] / 6;
      }
    }
    dp = ndp;
  }
  return dp[x];
}

int main() {
  int n, a, b; cin >> n >> a >> b;
  double ans = 0;
  for (int i = a; i <= b; ++i) ans += solve(i, n);
  cout << fixed << setprecision(6) << ans << '\n';
  return 0;
}

