#include <bits/stdc++.h>
using namespace std;

#define ll long long
typedef unsigned long long ull;
typedef __uint128_t L;

struct FastMod {

  ull b, m;

  FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}

  ull reduce(ull a) {
    ull q = (ull)((L(m) * a) >> 64), r = a - q * b;
    return r >= b ? r - b : r;
  }
};

FastMod fm(2);

vector<ll> fact;
vector<vector<int>> nCr;

int n, MOD;

ll p(ll x, ll y) {
  if (!y) return 1;
  ll b = p(x, y >> 1);
  b = b * b % (MOD + 1);
  if (y & 1) b *= x;
  return b % (MOD + 1);
}

ll get(int len, int base) {
  // Complimentary counts to find answer:
  vector<ll> dp(n / len + 1), dp2(n / len + 1); dp[0] = 1;
  for (int i = 1; i <= n / len; ++i) for (int j = 1; j <= i; ++j)
    dp[i] = fm.reduce(dp[i] + fm.reduce(fm.reduce(nCr[len * i - 1][len * j - 1] * fact[len * j - 1]) * dp[i - j]));
  for (int i = n / len; i >= 0; --i) {
    dp2[i] = fact[n - len * i];
    for (int j = i + 1; j <= n / len; ++j)
      dp2[i] = fm.reduce(dp2[i] - fm.reduce(fm.reduce(dp[j - i] * dp2[j]) * nCr[n - len * i][n - len * j]) + MOD);
  }
  return p(base, fm.reduce(fact[n] - dp2[0] + MOD));
}

int main() {
  ifstream in("exercise.in");
  ofstream out("exercise.out");
  in >> n >> MOD; --MOD;
  fm = FastMod(MOD);
  fact.resize(n + 1); fact[0] = 1; for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
  nCr = vector<vector<int>>(n + 1, vector<int>(n + 1));
  for (int i = 0; i <= n; ++i) nCr[i][0] = nCr[i][i] = 1;
  for (int i = 2; i <= n; ++i) for (int j = 1; j < i; ++j) nCr[i][j] = fm.reduce(nCr[i - 1][j - 1] + nCr[i - 1][j]);
  vector<int> sieve(n + 1), primes;
  for (int i = 2; i <= n; ++i) {
    if (!sieve[i]) primes.push_back(i);
    for (int j = i; j <= n; j += i) sieve[j] = i;
  }
  ll ans = 1;
  for (int num : primes) for (int base = num; base <= n; base *= num) ans = ans * get(base, num) % (MOD + 1);
  out << ans << '\n';
  return 0;
}
