#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void solve() {
  int n; cin >> n;
  vector<string> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  set<pair<int, int>> s;
  vector<int> cnts(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cnts[i] += arr[i][j] - '0';
    s.insert({cnts[i], i});
  }
  vector<vector<int>> ans(n);
  for (int i = 0; i < n; ++i) ans[i].push_back(i);
  while (s.size()) {
    pii fir = *s.begin(); s.erase(fir);
    for (int i = 0; i < n; ++i) {
      if (arr[i][fir.second] - '0') {
        ans[fir.second].push_back(i);
        s.erase({cnts[i], i}), s.insert({--cnts[i], i});
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    sort(ans[i].begin(), ans[i].end());
    cout << ans[i].size();
    for (int num : ans[i]) cout << ' ' << num + 1;
    cout << '\n';
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
