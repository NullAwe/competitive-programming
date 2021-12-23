#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7, INV_2 = 500000004;

int main() {
  int n, x; cin >> n >> x;
  vector<vector<int>> nCr(n + 1, vector<int>(n + 1));
  for (int i = 0; i <= n; ++i) nCr[i][0] = nCr[i][i] = 1;
  for (int i = 2; i <= n; ++i) for (int j = 1; j < i; ++j) nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]) % MOD;
  vector<ll> fact(n + 1); fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = (fact[i - 1] * i) % MOD;
  ll ans = 0;
  for (int i = 1; i < n; ++i) {
    int choices = n - x;
    ll chosen = nCr[choices][i];
    ll total = (((((chosen * fact[i]) % MOD) * x) % MOD) * fact[n - i - 1]) % MOD;
    ans = (ans + total) % MOD;
    for (int l = 1; l < x; ++l) {
      choices = (l - 1) + (n - x);
      chosen = nCr[choices][i - 1] - nCr[l - 1][i - 1];
      total = (((((((chosen * fact[i]) % MOD) * INV_2) % MOD) * (x - l)) % MOD) * fact[n - i - 1]) % MOD;
      ans = (ans + total) % MOD;
    }
  }
  // Output:
  cout << ans << endl;
  return 0;
}
