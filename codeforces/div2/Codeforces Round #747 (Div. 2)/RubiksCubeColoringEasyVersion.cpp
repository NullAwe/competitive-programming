#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;

ll pow(ll x, ll y, ll mod) {
  if (y == 0) return 1;
  ll base = pow(x, y / 2, mod);
  base *= base;
  base %= mod;
  if (y % 2 == 1) base *= x;
  return base % mod;
}

int main() {
  int n; cin >> n;
  // Output:
  cout << (6 * pow(4, pow(2, n, MOD - 1) + MOD - 3, MOD)) % MOD << endl;
  return 0;
}
