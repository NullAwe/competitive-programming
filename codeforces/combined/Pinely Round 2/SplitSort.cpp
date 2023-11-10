#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> pos(n); for (int i = 0; i < n; ++i) pos[arr[i] - 1] = i;
  int ans = 0;
  for (int i = 0; i < n - 1; ++i) if (pos[i] > pos[i + 1]) ++ans;
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
