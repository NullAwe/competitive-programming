#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  ll n; cin >> n;
  int k; cin >> k;
  vector<ll> primes(k); for (int i = 0; i < k; ++i) cin >> primes[i];
  // Calculates the answer using PIE:
  ll ans = 0;
  for (int i = 1; i < (1 << k); ++i) {
    int bits = __builtin_popcount(i), coef = pow(-1, bits - 1);
    ll mult = 1;
    bool canDo = true;
    for (int j = 0; j < k; ++j) {
      if (!(i & (1 << j))) continue;
      if (n / primes[j] < mult) {
        canDo = false;
        break;
      }
      mult *= primes[j];
    }
    if (!canDo) continue;
    ans += coef * (n / mult);
  }
  // Output:
  cout << ans << endl;
  return 0;
}
