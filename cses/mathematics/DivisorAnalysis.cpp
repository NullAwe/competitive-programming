#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MOD = 1e9 + 7;

ll _pow(ll x, ll y) {
  if (y <= 0) return 1;
  ll base = _pow(x, y >> 1);
  base = base * base;
  base %= MOD;
  if (y & 1) base *= x;
  return base % MOD;
}

ll p[100001], k[100001];

int main() {
  int n; cin >> n;
  for (int i = 0; i < n; i++) cin >> p[i] >> k[i];
  ll a = 1, b = 1, c = 1, d = 1;
  for (int i = 0; i < n; i++) {
    a = a * (k[i] + 1) % MOD;
    b = b * (_pow(p[i], k[i] + 1) - 1) % MOD * _pow(p[i] - 1, MOD - 2) % MOD;
    c = _pow(c, k[i] + 1) * _pow(_pow(p[i], (k[i] * (k[i] + 1) / 2)), d) % MOD;
    d = d * (k[i] + 1) % (MOD - 1);
  }
  cout << a << ' ' << b << ' ' << c << '\n';
  return 0;
}

