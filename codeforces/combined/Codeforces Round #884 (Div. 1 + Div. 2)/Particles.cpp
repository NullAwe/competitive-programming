#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<ll> sum(2);
  vector<bool> did(2);
  for (int i = 0; i < n; ++i)
    if (arr[i] >= 0) sum[i & 1] += arr[i], did[i & 1] = true;
  if (!did[0] && !did[1]) {
    int ans = INT_MIN;
    for (int num : arr) ans = max(ans, num);
    cout << ans << '\n';
    return;
  }
  if (!did[0]) cout << sum[1] << '\n';
  else if (!did[1]) cout << sum[0] << '\n';
  else cout << max(sum[0], sum[1]) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
