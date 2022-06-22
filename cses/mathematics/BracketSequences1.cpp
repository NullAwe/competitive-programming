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

ll inv(ll x) { return p(x, MOD - 2); }

int main() {
  int n; cin >> n;
  if (n & 1) {
    cout << 0 << '\n';
    return 0;
  }
  ll a, b, c = 1;
  for (int i = 1; i <= n; ++i) {
    c = c * i % MOD;
    if (i == (n >> 1)) a = c;
    else if (i == (n >> 1) + 1) b = c;
  }
  cout << (c * inv(a) % MOD) * inv(b) % MOD << '\n';
  return 0;
}

