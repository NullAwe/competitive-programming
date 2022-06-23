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
  int n, m; cin >> n >> m;
  int ans = 0, s[n + 1]; for (int i = 0; i <= n; ++i) s[i] = 0;
  for (int i = 1; i <= n; ++i) {
    if (n % i) continue;
    ll num = (p(m, i) - s[i] + MOD) % MOD;
    for (int j = i * 2; j <= n; j += i) s[j] = (s[j] + num) % MOD;
    ans = (ans + num * inv(i) % MOD) % MOD;
  }
  cout << ans << '\n';
  return 0;
}

