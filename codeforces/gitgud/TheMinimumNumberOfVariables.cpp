#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Precomputation:
  vector<bool> can(1 << (n - 1), false);
  for (int i = 0; i < n - 1; ++i)
    if (arr[i] * 2 == arr[i + 1]) can[1 << i] = true;
  for (int i = 1; i < (1 << (n - 1)); ++i) {
    if (__builtin_popcount(i) == 1) continue;
    int first = -1, last;
    for (int j = 0; j < n - 1; ++j) {
      if (i & (1 << j)) {
        if (first < 0) first = j;
        last = j;
      }
    }
    if (can[i ^ (1 << first)] || (arr[first] * 2 == arr[last + 1])) {
      can[i] = true;
      continue;
    }
    for (int j = first + 1; j < n - 1; ++j) {
      if (!(i & (1 << j))) continue;
      if (arr[first] + arr[j] == arr[last + 1]) {
        can[i] = true;
        break;
      }
    }
  }
  // Finds answer using dynamic programming:
  vector<bool> dp(1 << n, false);
  int sum = 1;
  dp[1] = true;
  for (int i = 1; i < n; ++i) {
    if (can[sum]) dp[sum + (1 << i)] = true;
    else break;
    sum += (1 << i);
  }
  for (int i = 1; i < (1 << n); ++i) {
    if (dp[i]) continue;
    for (int j = n - 1; j >= 0; --j) {
      if (!(i & (1 << j))) continue;
      int without = i ^ (1 << j);
      if ((i & (1 << (j - 1)))) {
        for (int k = 0; k < j; ++k) {
          if ((i & (1 << k))) continue;
          if (can[without | (1 << k)] && dp[without | (1 << k)]) {
            dp[i] = true;
            break;
          }
        }
      } else {
        without |= (1 << (j - 1));
        if (can[without] && dp[without]) dp[i] = true;
      }
      break;
    }
  }
  int ans = INT_MAX;
  for (int i = 0; i < (1 << (n - 1)); ++i) {
    int a = __builtin_popcount(i) + 1;
    if (dp[i | (1 << (n - 1))]) ans = min(ans, a);
  }
  // Output:
  cout << (ans == INT_MAX ? -1 : ans) << endl;
}
