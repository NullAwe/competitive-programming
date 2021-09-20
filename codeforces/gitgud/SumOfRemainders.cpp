#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;

int main() {
  ll n, m; cin >> n >> m;
  ll ans = 0;
  if (m > n) {
    ans = (((m - n) % MOD) * (n % MOD))	% MOD;
    m = n;
  }
  ll doing = m;
  while (doing > 0) {
    ll start = (n % doing) % MOD, diff = (n / doing) % MOD,
      num = (doing - n / (n / doing + 1)) % MOD;
    doing = n / (n / doing + 1);
    ans = (ans + (((num * ((2 * start + diff * (num - 1 + MOD)) % MOD) % MOD) % MOD) * (MOD + 1) / 2) % MOD) % MOD;
  }
  // Output:
  cout << ans << endl;
  return 0;
}
