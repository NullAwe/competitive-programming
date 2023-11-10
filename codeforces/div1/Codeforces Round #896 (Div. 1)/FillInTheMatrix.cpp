#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> arr(n, vector<int>(m));
  for (int i = 0; i < m; ++i) {
    int at = n;
    while (at >= m) {
      arr[n - at][(i + 1) % m] = i;
      --at;
    }
    int plus = 1;
    while (at > 0) {
      arr[n - at][(i + plus) % m] = i;
      ++plus, --at;
    }
  }
  set<int> mxs;
  for (int i = 0; i < m; ++i) {
    set<int> tmx;
    for (int j = 0; j < n; ++j) tmx.insert(arr[j][i]);
    for (int j = 0; j <= n; ++j) {
      if (!tmx.count(j)) {
        mxs.insert(j);
        break;
      }
    }
  }
  for (int i = 0; i <= m; ++i) {
    if (!mxs.count(i)) {
      cout << i << '\n';
      break;
    }
  }
  for (vector<int> ar : arr) {
    for (int num : ar) cout << num << ' ';
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
