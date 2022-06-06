#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> dp(n + 1);
  for (int i = 1; i <= n; ++i) {
    dp[i] = INT_MAX;
    int temp = i;
    while (temp) {
      int digit = temp % 10; temp /= 10;
      if (digit) dp[i] = min(dp[i], dp[i - digit] + 1);
    }
  }
  cout << dp[n] << '\n';
  return 0;
}
