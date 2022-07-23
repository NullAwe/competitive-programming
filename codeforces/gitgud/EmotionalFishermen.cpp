#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
  int n; cin >> n;
  vector<int> arr(n), lefts(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  int l = 0;
  for (int i = 0; i < n; ++i) {
    while (l < i && 2 * arr[l] <= arr[i]) ++l;
    lefts[i] = l;
  }
  vector<int> dp(n + 1, 1);
  for (int i = 0; i < n; ++i) {
    vector<int> ndp(n);
    for (int j = 0; j < n; ++j) ndp[j] = ((long long) (dp[j + 1] - dp[j] + MOD) * max(lefts[j] - i + 1, 0) % MOD + dp[lefts[j]]) % MOD;
    dp[0] = 0;
    for (int j = 0; j < n; ++j) dp[j + 1] = (dp[j] + ndp[j]) % MOD;
  }
  cout << dp[n] << '\n';
  return 0;
}

