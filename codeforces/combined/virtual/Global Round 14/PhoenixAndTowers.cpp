#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m, x; cin >> n >> m >> x;
  vector<pair<int, int>> arr(n);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    arr[i] = {a, i};
  }
  sort(arr.begin(), arr.end());
  vector<int> ans(n);
  for (int i = 0; i < n; ++i) ans[arr[i].second] = i % m + 1;
  // Output:
  cout << "YES\n";
  for (int num : ans) cout << num << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
