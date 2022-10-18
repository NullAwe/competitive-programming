#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n), ans(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  set<int> remain; for (int i = 1; i <= n; ++i) remain.insert(i);
  for (int i = 1; i < n; ++i) {
    int diff = arr[i - 1] - arr[i], num = *remain.lower_bound(diff);
    ans[num - 1] = i + 1, remain.erase(num);
  }
  ans[*remain.begin() - 1] = 1;
  for (int num : ans) cout << num << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
