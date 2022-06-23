#include <iostream>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

struct TTM {

  ll a, b, c, d;

  TTM(ll a, ll b, ll c, ll d) : a(a), b(b), c(c), d(d) {}

  TTM operator*(TTM ttm) {
    return TTM((a * ttm.a + c * ttm.b) % MOD, (b * ttm.a + d * ttm.b) % MOD, (a * ttm.c + c * ttm.d) % MOD, (b * ttm.c + d * ttm.d) % MOD);
  }
};

TTM p(ll y) {
  if (!y) return TTM(1, 0, 0, 1);
  TTM b = p(y >> 1);
  b = b * b;
  if (y & 1) b = b * TTM(0, 1, 1, 1);
  return b;
}

int main() {
  ll n; cin >> n;
  cout << p(n).c << '\n';
  return 0;
}

