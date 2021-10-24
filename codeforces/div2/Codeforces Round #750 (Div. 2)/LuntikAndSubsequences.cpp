#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int z = 0, o = 0;
  for (int num : arr) {
    if (num == 0) ++z;
    else if (num == 1) ++o;
  }
  ll ans = o;
  for (int i = 0; i < z; ++i) ans *= 2;
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}