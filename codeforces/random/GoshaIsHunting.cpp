#include <bits/stdc++.h>
using namespace std;

const double EPS = 5e-8;

int n, a, b;
vector<double> aa, bb;

pair<double, int> getUltras(double cost) {
  vector<vector<pair<double, int>>> dp(n + 1, vector<pair<double, int>>(a + 1));
  for (int i = 1; i <= n; ++i) {
    dp[i][0].first = dp[i - 1][0].first + (bb[i - 1] >= cost ? bb[i - 1] - cost : 0);
    dp[i][0].second = dp[i - 1][0].second + (bb[i - 1] >= cost);
    for (int j = 1; j <= a; ++j) {
      dp[i][j].first = dp[i - 1][j].first + (bb[i - 1] >= cost ? bb[i - 1] - cost : 0);
      dp[i][j].second = dp[i - 1][j].second + (bb[i - 1] >= cost);
      pair<double, int> test;
      test.first = dp[i - 1][j - 1].first + aa[i - 1];
      test.second = dp[i - 1][j - 1].second;
      if ((1 - aa[i - 1]) * bb[i - 1] >= cost) {
        test.first += (1 - aa[i - 1]) * bb[i - 1] - cost;
        test.second++;
      }
      if (test.first >= dp[i][j].first) dp[i][j] = test;
    }
  }
  return dp[n][a];
}

int main() {
  cout << setprecision(17) << fixed;
  cin >> n >> a >> b;
  aa.resize(n), bb.resize(n);
  for (int i = 0; i < n; ++i) cin >> aa[i];
  for (int i = 0; i < n; ++i) cin >> bb[i];
  double lo = 0.0, hi = 1.1, ans = 0;
  while (hi - lo > EPS) {
    double mid = (lo + hi) / 2;
    pair<double, int> ultras = getUltras(mid);
    if (ultras.second > b) lo = mid;
    else hi = mid, ans = ultras.first;
  }
  cout << ans + (hi * b) << '\n';
  return 0;
}
