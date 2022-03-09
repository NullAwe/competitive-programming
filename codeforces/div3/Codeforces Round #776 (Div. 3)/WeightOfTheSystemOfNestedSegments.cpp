#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<pair<int, int>> arr(m); for (int i = 0; i < m; ++i) cin >> arr[i].second >> arr[i].first;
  map<int, int> ma; for (int i = 0; i < m; ++i) ma[arr[i].second] = i + 1;
  sort(arr.begin(), arr.end());
  vector<int> use(2 * n); for (int i = 0; i < 2 * n; ++i) use[i] = arr[i].second;
  sort(use.begin(), use.end());
  int weight = 0;
  for (int i = 0; i < 2 * n; ++i) weight += arr[i].first;
  cout << weight << '\n';
  for (int i = 0; i < n; ++i) cout << ma[use[i]] << ' ' << ma[use[2 * n - i - 1]] << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
