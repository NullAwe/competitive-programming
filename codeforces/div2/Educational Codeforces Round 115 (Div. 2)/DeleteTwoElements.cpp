#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  ll sum = 0;
  for (int num : arr) sum += num;
  if (sum * 2 % n > 0) {
    // Output:
    cout << 0 << endl;
    return;
  }
  sum = sum * 2 / n;
  map<ll, int> m;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += m[sum - arr[i]];
    ++m[arr[i]];
  }
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
