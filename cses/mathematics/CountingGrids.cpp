#include <iostream>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

ll p(ll x, ll y) {
  if (!y) return 1;
  ll base = p(x, y >> 1);
  base = base * base % MOD;
  if (y & 1) base *= x;
  return base % MOD;
}

int main() {
  ll n; cin >> n;
  ll h = n >> 1, f = 2 * h == n ? h * h : h * h + h + 1, t = 2 * h == n ? h * n : h * n + h + 1, o = n * n;
  ll a = p(2, f), b = (p(2, t) - a + MOD) % MOD, c = (p(2, o) - a - b + 2 * MOD) % MOD;
  cout << (a + b * 500000004 % MOD + c * 250000002 % MOD) % MOD << '\n';
  return 0;
}

