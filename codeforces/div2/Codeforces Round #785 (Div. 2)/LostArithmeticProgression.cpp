#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

ll _gcd(ll a, ll b) {
  if (b == 0) return a;
  return _gcd(b, a % b);
}

ll _lcm(ll a, ll b) {
  return a * b / _gcd(a, b);
}

void solve() {
  ll b, q, y; cin >> b >> q >> y;
  ll c, r, z; cin >> c >> r >> z;
  if (c < b || c + r * (z - 1) > b + q * (y - 1) || (c - b) % q) {
    cout << "0\n";
    return;
  }
  vector<ll> factors; factors.reserve(4e4);
  for (int i = 1; i * i <= r; ++i) {
    if (r % i == 0) {
      factors.push_back(i);
      if (r / i != i) factors.push_back(r / i);
    }
  }
  ll ans = 0;
  for (ll fac : factors) {
    if (_lcm(q, fac) != r) continue;
    if (c - r < b || c + r * z > b + q * (y - 1)) {
      cout << "-1\n";
      return;
    }
    ll extend = r / fac;
    ans = (ans + extend * extend) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
