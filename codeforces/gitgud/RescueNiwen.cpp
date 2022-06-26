#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  vector<vector<int>> p(n + 1, vector<int>(n + 1));
  for (int i = n - 1; i >= 0; --i) {
    for (int j = n - 1; j >= 0; --j) {
      if (i == j) p[i][j] = n - i;
      else if (s[i] != s[j]) p[i][j] = 0;
      else p[i][j] = p[i + 1][j + 1] + 1;
    }
  }
  vector<int> dp(n + 1);
  for (int i = 0; i < n; ++i) {
    dp[i + 1] = n - i;
    for (int j = i - 1; j >= 0; --j) {
      int len = p[i][j];
      if (len == n - i || s[i + len] < s[j + len]) continue;
      dp[i + 1] = max(dp[i + 1], dp[j + 1] + n - i - len);
    }
  }
  int ans = 0; for (int num : dp) ans = max(ans, num);
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

