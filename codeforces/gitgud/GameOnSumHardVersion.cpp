#include <iostream>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;
const int MAX_N = 1e6 + 1;

ll fact[MAX_N], twos[MAX_N];

ll p(int x, int y) {
  if (y <= 0) return 1;
  ll base = p(x, y >> 1);
  base *= base;
  base %= MOD;
  if (y & 1) base *= x;
  return base % MOD;
}

inline ll inv(int x) {
  return p(x, MOD - 2);
}

inline ll nCr(int n, int r) {
  return (fact[n] * inv(fact[r]) % MOD) * inv(fact[n - r]) % MOD;
}

void solve() {
  int n, m, k; cin >> n >> m >> k;
  if (n == m) {
    cout << (ll) n * k % MOD << '\n';
    return;
  }
  if (m == 0) {
    cout << 0 << '\n';
    return;
  }
  int up = m, down = n - m;
  ll sum = 0;
  for (int i = 1; i <= up; ++i) {
    sum += (i * nCr(n - i - 1, down - 1) % MOD) * twos[i - 1] % MOD;
    sum %= MOD;
  }
  sum = sum * k % MOD;
  cout << (sum * inv(twos[n - 1])) % MOD << '\n';
}

int main() {
  fact[0] = 1; for (int i = 1; i < MAX_N; ++i) fact[i] = fact[i - 1] * i % MOD;
  twos[0] = 1; for (int i = 1; i < MAX_N; ++i) twos[i] = twos[i - 1] * 2 % MOD;
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
