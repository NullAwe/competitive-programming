#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll x; cin >> x;
  vector<ll> pref(n + 1); for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + arr[i];
  int ans = 1, first = 0, la = (arr[0] < x ? 0 : -1);
  for (int i = 1; i < n; ++i) {
    if (i != first && (pref[i + 1] - pref[first] < (i - first + 1) * x ||
        (i > first && arr[i - 1] + arr[i] < 2 * x) || (la >= 0 && pref[i + 1] - pref[la] < (i - la + 1) * x))) {
      first = i + 1;
      la = (arr[first] < x ? first : -1);
      continue;
    }
    if (arr[i] < x) la = i;
    ++ans;
  }
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
