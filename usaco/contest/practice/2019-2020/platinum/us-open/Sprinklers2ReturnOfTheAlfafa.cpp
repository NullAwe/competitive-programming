#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

int main() {
  ifstream in("sprinklers2.in");
  ofstream out("sprinklers2.out");
  int n; in >> n;
  vector<ll> p2(n + 1); p2[0] = 1; for (int i = 1; i <= n; ++i) p2[i] = p2[i - 1] * 2 % MOD;
  vector<string> arr(n); for (int i = 0; i < n; ++i) in >> arr[i];
  vector<ll> dp(n + 1), fake(n + 1);
  vector<int> spots(n + 1); for (int i = 0; i < n; ++i) spots[i + 1] = spots[i] + (arr[0][i] == '.');
  for (int i = 0; i < n; ++i) {
    if (i && arr[0][i - 1] == 'W') continue;
    int a = i ? spots[i - 1] : 0, b = spots[n] - spots[i + 1];
    fake[i] = p2[a] * p2[b] % MOD;
    if (arr[0][i] == '.') dp[i] = fake[i];
  }
  if (arr[0][n - 1] == '.') dp[n] = p2[spots[n - 1]];
  vector<ll> pdp(n + 1); for (int i = 0; i < n; ++i) pdp[i + 1] = (pdp[i] + dp[i]) % MOD;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < n; ++j) spots[j + 1] = spots[j] + (arr[i][j] == '.');
    vector<ll> ndp(n + 1), nfake(n + 1);
    for (int j = 0; j < n; ++j) {
      int a = spots[j], b = spots[n] - spots[j + 1];
      nfake[j] = (dp[j] + fake[j]) * p2[a] % MOD * p2[b] % MOD;
      if (arr[i][j] == '.') ndp[j] = nfake[j];
      if (i && arr[i][j - 1] == 'W') continue;
      ll val = pdp[j] * p2[max(a - 1, 0)] % MOD * p2[b];
      nfake[j] = (nfake[j] + val) % MOD;
      if (arr[i][j] == '.') ndp[j] = (ndp[j] + val) % MOD;
    }
    ndp[n] = dp[n] * p2[spots[n]] % MOD;
    if (arr[i][n - 1] == '.') ndp[n] = (ndp[n] + pdp[n] * p2[spots[n - 1]]) % MOD;
    dp = ndp, fake = nfake;
    for (int i = 0; i < n; ++i) pdp[i + 1] = (pdp[i] + dp[i]) % MOD;
  }
  ll ans = 0;
  for (ll num : dp) ans += num;
  out << ans % MOD << '\n';
  return 0;
}
