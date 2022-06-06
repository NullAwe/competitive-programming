#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<pll>> dp(n, vector<pll>(n));
  for (int len = 1; len <= n; ++len) {
    for (int i = 0; i + len <= n; ++i) {
      int j = i + len - 1;
      bool first = !((n - len) & 1);
      pll a, b, use;
      if (len > 1) a = dp[i + 1][j], b = dp[i][j - 1];
      else a = {0, 0}, b = {0, 0};
      if (first) a.first += arr[i], b.first += arr[j];
      else a.second += arr[i], b.second += arr[j];
      if (first) use = a.first > b.first ? a : b;
      else use = a.second > b.second ? a : b;
      dp[i][j] = use;
    }
  }
  cout << dp[0][n - 1].first << '\n';
  return 0;
}
