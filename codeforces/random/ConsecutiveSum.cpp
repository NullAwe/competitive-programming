#include <iostream>
using namespace std;

#define ll long long

void solve() {
  int n, k; cin >> n >> k;
  int arr[n]; for (int i = 0; i < n; ++i) cin >> arr[i];
  ll ans = 0;
  for (int i = 0; i < k; ++i) {
    int mx = 0;
    for (int j = i; j < n; j += k) mx = max(mx, arr[j]);
    ans += mx;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
