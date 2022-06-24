#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  vector<double> dp(k, 1.0 / k);
  for (int i = 1; i < n; ++i) {
    double sum = 0;
    for (int j = 0; j < k; ++j) {
      sum += dp[j];
      dp[j] = dp[j] * j / k + sum / k;
    }
  }
  double ans = 0; for (int i = 0; i < k; ++i) ans += (i + 1) * dp[i];
  cout << fixed << setprecision(6) << ans << '\n';
  return 0;
}

