#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>

const int MAX_N = 100000;
const int LOG = 58; // log2(max(A))

int main() {
  // Input:
  int n; cin >> n;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll mx = 0; for (ll num : arr) mx = max(mx, num);
  // Flips the numbers, such that we can work with addition instead of subtraction (much easier):
  for (int i = 0; i < n; ++i) arr[i] = mx - arr[i];
  // When thinking about the problem, start thinking from here (everything before assume correctness of transform):
  vector<pll> brr(n); for (int i = 0; i < n; ++i) brr[i] = {arr[i], i};
  // Ordered radix sort for each bit [O(n log n)]:
  vector<vector<pll>> saves(LOG);
  saves[0] = brr;
  for (int i = 0; i < LOG - 1; ++i) {
    // Orders based off of all bits less than or equal to current (if strictly less than (suspected), please alter):
    vector<vector<pll>> arrs(2);
    for (int j = 0; j < n; ++j) arrs[(brr[j].first >> i) & 1].push_back(brr[j]);
    for (pll p : arrs[0]) saves[i + 1].push_back(p);
    for (pll p : arrs[1]) saves[i + 1].push_back(p);
    brr = saves[i + 1];
  }
  // For now, we assume that once something carries, it's not under our jursidiction, so we don't care about it.
  // Base case will originally have all 0s, so the # of 1s is just the number of carries, UNLESS we set all 1s:
  int dp[LOG][n + 1][2]; // [current bit][suffix carried (thx PurpleCrayon :blobheart)][1 added or not]
  // Base case:
  for (int carry = 0; carry <= n; ++carry)
    dp[LOG - 1][carry][0] = carry, dp[LOG - 1][carry][1] = n;
  /*
  Explanation:
  - If we do not add the 1, the answer is just the carry (everything else is just 0).
  - If we do add the 1, we get n extra 1s no matter what (thus carry does not matter).
  */
  // DP computation:
  for (int i = LOG - 2; i >= 0; --i) {
    // Start with adding 0:
    int ones = 0;
    for (int j = 0; j < n; ++j) ones += (arr[j] >> i) & 1;
    int carried = 0;
    // Carry everything from next bit [j, n):
    dp[i][0][0] = min(dp[i + 1][carried][0], dp[i + 1][carried][1]) + ones;
    for (int j = n - 1; j >= 0; --j) {
      int ind = saves[i][j].second;
      if ((arr[ind] >> i) & 1) --ones, ++carried;
      else ++ones;
      dp[i][n - j][0] = min(dp[i + 1][carried][0], dp[i + 1][carried][1]) + ones;
    }
    // Finish with adding 1:
    ones = n;
    for (int j = 0; j < n; ++j) ones -= (arr[j] >> i) & 1;
    carried = n - ones;
    // Carry everything from next bit [j, n):
    dp[i][0][1] = min(dp[i + 1][carried][0], dp[i + 1][carried][1]) + ones;
    for (int j = n - 1; j >= 0; --j) {
      int ind = saves[i][j].second;
      if ((arr[ind] >> i) & 1) ++ones;
      else --ones, ++carried;
      dp[i][n - j][1] = min(dp[i + 1][carried][0], dp[i + 1][carried][1]) + ones;
    }
  }
  // Output: from bit 0, none carried because last bit didn't exist:
  cout << min(dp[0][0][0], dp[0][0][1]) << '\n';
  return 0;
}
