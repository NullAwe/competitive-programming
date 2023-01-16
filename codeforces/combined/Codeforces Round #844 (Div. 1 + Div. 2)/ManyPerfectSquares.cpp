#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline bool isq(ll x) {
  ll lo = -1, hi = min((ll) sqrt(x) + 5, x + 1);
  while (lo < hi - 1) {
    ll mid = (lo + hi) >> 1;
    if (mid * mid > x) hi = mid;
    else if (mid * mid == x) return true;
    else lo = mid;
  }
  return false;
}

inline void solve() {
  int n; cin >> n;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int ans = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int num = arr[j] - arr[i];
      if (num % 4 && num % 2 == 0) continue;
      for (int k = 1; k * k <= num; ++k) {
        if (num % k || k % 2 != (num / k) % 2) continue;
        ll a = k + (num / k - k) / 2, b = a - k, sq1 = a * a;
        if (sq1 < arr[j]) continue;
        int cont = 2;
        for (int l = j + 1; l < n; ++l) if (isq(sq1 + arr[l] - arr[j])) ++cont;
        ans = max(ans, cont);
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
