#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll INF = LLONG_MAX >> 2;

void solve() {
  int n, x, y; cin >> n >> x >> y;
  string a, b, c; cin >> a >> b;
  for (int i = 0; i < n; ++i) c += a[i] == b[i] ? "0" : "1";
  int p = 0; for (int i = 0; i < n; ++i) p += c[i] - '0';
  if (p & 1) {
    cout << -1 << '\n';
    return;
  }
  if (x > y) {
    bool adj = false;
    for (int i = 1; i < n; ++i) if (c[i] == '1' && c[i - 1] == '1') adj = true;
    if (!adj || p > 2) cout << (ll) (p / 2) * y << '\n';
    else cout << min(x, 2 * y) << '\n';
    return;
  }
  vector<vector<ll>> dp(2, vector<ll>(n + 1, INF));
  dp[c[0] - '0'][c[0] - '0'] = 0;
  for (int i = 1; i < n; ++i) {
    vector<vector<ll>> ndp(2, vector<ll>(n + 1, INF));
    int sub = c[i] - '0';
    for (int j = 0; j <= i; ++j) {
      if (c[i] == '0') {
        ndp[0][j] = min(dp[0][j], dp[1][j]);
        ndp[1][j] = min(ndp[1][j], min(dp[0][j] + y, dp[1][j] + x));
        if (j > 1) ndp[1][j] = min(ndp[1][j], min(dp[0][j - 2] + x, dp[1][j - 2] + y));
      } else {
        if (j) ndp[1][j] = min(dp[0][j - 1], dp[1][j - 1]);
        if (j) ndp[0][j] = min(ndp[0][j], min(dp[0][j - 1] + x, dp[1][j - 1] + y));
        if (j < i) ndp[0][j] = min(ndp[0][j], min(dp[0][j + 1] + y, dp[1][j + 1] + x));
      }
    }
    dp = ndp;
  }
  cout << min(dp[0][0], dp[1][0]) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
