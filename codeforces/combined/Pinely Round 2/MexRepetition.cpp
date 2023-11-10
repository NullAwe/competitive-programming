#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n, k; cin >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> ans(n + 1);
  set<int> s; for (int num : arr) s.insert(num);
  for (int i = 0; i <= n; ++i) if (!s.count(i)) arr.push_back(i);
  for (int i = 0; i <= n; ++i) {
    ans[i] = arr[((i - k) % (n + 1) + n + 1) % (n + 1)];
  }
  for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
