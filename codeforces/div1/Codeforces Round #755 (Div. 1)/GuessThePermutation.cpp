#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll n; cin >> n;
  // Finds upper number:
  ll lo = 0, hi = n + 1;
  printf("? %lld %lld\n", 1LL, n); fflush(stdout);
  ll m; scanf("%lld", &m);
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    printf("? %lld %lld\n", 1LL, mid); fflush(stdout);
    ll res; scanf("%lld", &res);
    if (res == m) hi = mid;
    else lo = mid;
  }
  // Finds middle number:
  printf("? %lld %lld\n", 1LL, hi - 1); fflush(stdout);
  ll lm; scanf("%lld", &lm);
  ll diff = m - lm, k = hi;
  m -= (diff * (diff + 1)) / 2;
  hi -= diff;
  ll j = hi;
  --hi;
  // Finds lower number:
  printf("? %lld %lld\n", 1LL, hi - 1); fflush(stdout);
  scanf("%lld", &lm);
  diff = m - lm;
  m -= (diff * (diff + 1)) / 2;
  hi -= diff;
  // Output:
  printf("! %lld %lld %lld\n", hi, j, k);
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
