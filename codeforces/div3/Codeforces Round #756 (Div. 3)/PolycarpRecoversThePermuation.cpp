#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Output:
  if (arr[0] == n || arr[n - 1] == n) for (int i = n - 1; i >= 0; --i) cout << arr[i] << ' ';
  else cout << -1;
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
