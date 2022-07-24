#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

int main() {
  string str; cin >> str;
  int n = str.size();
  vector<int> fix = {0, 2, 4, 1, 1, 4, 2, 0}, brk = {0, 0, 0, 6, 6, 0, 0, 0};
  vector<ll> dp(64); dp[0] = 1;
  for (int i = 0; i < n; ++i) {
    vector<ll> ndp(64);
    bool bit = str[i] - '0';
    for (int t = 0; t < 8; ++t) {
      for (int l = 0; l < 8; ++l) {
        if (!bit && (t & l) != t) continue;
        for (int sat = 0; sat < 8; ++sat) {
          if ((sat & brk[t]) != brk[t]) continue;
          int nw = sat | fix[t], nl = l | (bit ? t ^ 7 : 0);
          ndp[(nw << 3) + nl] = (ndp[(nw << 3) + nl] + dp[(sat << 3) + l]) % MOD;
        }
      }
    }
    dp = ndp;
  }
  ll ans = 0;
  for (int i = 0; i < 8; ++i) ans = (ans + dp[i + 56]) % MOD;
  cout << (3 * ans) % MOD << '\n';
  return 0;
}
