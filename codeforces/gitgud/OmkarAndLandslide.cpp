#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  ll sum = 0; for (int i = 0; i < n; ++i) { ll x; cin >> x; sum += x; }
  ll lo = 0, hi = 1e12;
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    if ((2 * mid + n - 1) * n / 2 <= sum) lo = mid;
    else hi = mid;
  }
  if ((2 * lo + n - 1) * n / 2 == sum) {
    for (ll i = lo; i < lo + n; ++i) cout << i << ' ';
    cout << '\n';
    return 0;
  }
  --n;
  lo = 0, hi = 1e12;
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    ll rep = sum - (2 * mid + n - 1) * n / 2;
    if (rep >= 0 && mid <= rep) lo = mid;
    else hi = mid;
  }
  ll rep = sum - (2 * lo + n - 1) * n / 2;
  for (ll i = lo; i < lo + n; ++i) {
    cout << i << ' ';
    if (i == rep) cout << i << ' ';
  }
  cout << '\n';
  return 0;
}

