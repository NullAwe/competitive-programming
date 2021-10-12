#include <bits/stdc++.h>
using namespace std;

const int MAX_LEN = 400001;

int main() {
  int n; cin >> n;
  vector<string> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<int>> starting(n, vector<int>(MAX_LEN));
  vector<int> diffs(n), minDiff(n), inds(n);
  for (int i = 0; i < n; ++i) inds[i] = i;
  for (int i = 0; i < n; ++i) {
    int diff = 0, minStart = 0;
    for (int j = 0; j < arr[i].size(); ++j) {
      if (arr[i][j] == '(') ++diff;
      else --diff;
      if (-diff >= minStart) ++starting[i][-diff];
      minStart = max(minStart, -diff);
      minDiff[i] = min(minDiff[i], diff);
    }
    diffs[i] = diff;
  }
  // Finds answer using bitmask dynamic programming:
  vector<pair<pair<int, int>, bool>> dp(1 << n, {{0, 0}, false});
  dp[0] = {{0, 0}, true};
  int ans = 0;
  for (int i = 1; i < (1 << n); ++i) {
    for (int j = 0; j < n; ++j) {
      if (!(i & (1 << j))) continue;
      int without = i ^ (1 << j);
      if (!dp[without].second) continue;
      int diff = dp[without].first.second;
      ans = max(ans, dp[without].first.first + starting[j][diff]);
      if (diff + minDiff[j] < 0) continue;
      dp[i] = {{dp[i].first.first, diff + diffs[j]}, true};
      dp[i].first.first = max(dp[i].first.first, dp[without].first.first + starting[j][diff]);
    }
  }
  // Output:
  cout << ans << endl;
  return 0;
}
