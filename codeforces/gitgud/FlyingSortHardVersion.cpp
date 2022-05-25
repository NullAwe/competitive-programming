#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> sorted = arr; sort(sorted.begin(), sorted.end());
  map<int, int> m;
  int id = 1;
  for (int i = 1; i < n; ++i) if (sorted[i] != sorted[i - 1]) m[sorted[i]] = id++;
  for (int i = 0; i < n; ++i) arr[i] = m[arr[i]];
  vector<int> count(id); for (int num : arr) ++count[num];
  vector<vector<int>> inds(id);
  // Index 0: still on the first number (continue whenever)
  // Index 1: can't continue now, can't continue ever
  // Index 2: can't continue now, but can continue later
  // Index 3: should continue now
  vector<vector<int>> sizes(n, vector<int>(4));
  for (int i = 0; i < n; ++i) {
    --count[arr[i]];
    int l = 0, l2 = 0;
    if (inds[arr[i]].size()) l = inds[arr[i]][inds[arr[i]].size() - 1];
    if (arr[i] && inds[arr[i] - 1].size()) l2 = inds[arr[i] - 1][inds[arr[i] - 1].size() - 1];
    // Index 0:
    sizes[i][0] = inds[arr[i]].size() ? sizes[l][0] + 1 : 1;
    // Index 1:
    if (inds[arr[i]].size()) sizes[i][1] = sizes[l][1] + 1;
    if (arr[i] && inds[arr[i] - 1].size() && inds[arr[i]].size()) sizes[i][1] = max(sizes[i][1], max(sizes[l2][0], sizes[l2][3]) + 1);
    // Index 2:
    if (!inds[arr[i]].size()) sizes[i][2] = 1;
    if (inds[arr[i]].size()) sizes[i][2] = sizes[l][2] + 1;
    else if (arr[i] && inds[arr[i] - 1].size()) sizes[i][2] = max(sizes[l2][0], sizes[l2][3]) + 1;
    // Index 3:
    if (!count[arr[i]]) {
      if (!inds[arr[i]].size()) sizes[i][3] = 1;
      if (inds[arr[i]].size()) sizes[i][3] = sizes[l][2] + 1;
      else if (arr[i] && inds[arr[i] - 1].size()) sizes[i][3] = max(sizes[l2][0], sizes[l2][3]) + 1;
    }
    inds[arr[i]].push_back(i);
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < 4; ++j) ans = max(ans, sizes[i][j]);
  cout << n - ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
