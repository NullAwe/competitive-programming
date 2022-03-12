#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int ans = n + 1;
  for (int i = 0; i < n; ++i) {
    if (!arr[i]) break;
    --ans;
  }
  for (int i = n - 1; i >= 0; --i) {
    if (!arr[i]) break;
    --ans;
  }
  cout << max(ans, 0) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
