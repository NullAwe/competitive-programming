#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int ans = arr[0] > 0;
  for (int i = 1; i < n; ++i) if (arr[i] && !arr[i - 1]) ++ans;
  cout << min(ans, 2) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
