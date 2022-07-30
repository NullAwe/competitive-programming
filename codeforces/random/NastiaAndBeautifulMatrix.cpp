#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void solve() {
  int n, m; cin >> n >> m;
  vector<int> nums(m); for (int i = 0; i < m; ++i) cin >> nums[i];
  int mx = 0;
  for (int num : nums) mx = max(mx, num);
  int sz = 1;
  while (sz * sz - (sz / 2) * (sz / 2) < n || sz * ((sz + 1) / 2) < mx) ++sz;
  vector<pii> order; order.reserve(sz * sz - (sz / 2) * (sz / 2));
  for (int i = 0; i < sz; i += 2) for (int j = 1; j < sz; j += 2) order.push_back({i, j});
  for (int i = 0; i < sz; i += 2) for (int j = 0; j < sz; j += 2) order.push_back({i, j});
  for (int i = 1; i < sz; i += 2) for (int j = 0; j < sz; j += 2) order.push_back({i, j});
  vector<pii> ins(m); for (int i = 0; i < m; ++i) ins[i] = {nums[i], i + 1};
  sort(ins.begin(), ins.end()), reverse(ins.begin(), ins.end());
  int ind = 0;
  vector<vector<int>> ans(sz, vector<int>(sz));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < ins[i].first; ++j) {
      pii pos = order[ind++];
      ans[pos.first][pos.second] = ins[i].second;
    }
  }
  cout << sz << '\n';
  for (vector<int> arr : ans) {
    for (int num : arr) cout << num << ' ';
    cout << '\n';
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

