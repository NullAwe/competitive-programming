#include <iostream>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;
const int MAX_N = 1e6 + 1;

ll fact[MAX_N];

ll p(ll x, ll y) {
  if (!y) return 1;
  ll base = p(x, y >> 1);
  base = base * base % MOD;
  if (y & 1) base *= x;
  return base % MOD;
}

ll inv(ll x) { return p(x, MOD - 2); }

int main() {
  fact[0] = 1; for (int i = 1; i < MAX_N; ++i) fact[i] = fact[i - 1] * i % MOD;
  int n; cin >> n;
  string prefix; cin >> prefix;
  if (n & 1) {
    cout << 0 << '\n';
    return 0;
  }
  int l = 0, r = 0;
  for (int i = 0; i < prefix.size(); ++i) {
    if (prefix[i] == '(') ++l;
    else ++r;
    if (r > l) {
      cout << 0 << '\n';
      return 0;
    }
  }
  if (l * 2 > n) {
    cout << 0 << '\n';
    return 0;
  }
  ll ans = (fact[n - l - r] * inv(fact[(n >> 1) - l]) % MOD) * inv(fact[(n >> 1) - r]) % MOD;
  ans -= (fact[n - l - r] * inv(fact[(n >> 1) - l - 1]) % MOD) * inv(fact[(n >> 1) - r + 1]) % MOD;
  ans += MOD;
  cout << ans % MOD << '\n';
  return 0;
}

