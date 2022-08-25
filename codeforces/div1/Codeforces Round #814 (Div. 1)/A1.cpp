#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int ans = 0, last = -1;
  for (int i = 0; i < n; ++i) {
    int _xor = 0;
    for (int j = i - 1; j > last; --j) {
      if (_xor == arr[i]) {
        last = i;
        break;
      }
      _xor ^= arr[j];
    }
    if (_xor == arr[i]) last = i;
    if (last == i) continue;
    ++ans;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
