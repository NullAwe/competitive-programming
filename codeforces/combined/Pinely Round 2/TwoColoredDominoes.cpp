#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n, m; cin >> n >> m;
  vector<string> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < m; ++j) if (arr[i][j] != '.') ++cnt;
    if (cnt & 1) {
      cout << -1 << '\n';
      return;
    }
  }
  for (int j = 0; j < m; ++j) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) if (arr[i][j] != '.') ++cnt;
    if (cnt & 1) {
      cout << -1 << '\n';
      return;
    }
  }
  for (int j = 0; j < m; ++j) {
    bool black = true;
    for (int i = 0; i < n; ++i) {
      if (arr[i][j] == 'L') {
        arr[i][j] = black ? 'B' : 'W';
        arr[i][j + 1] = black ? 'W' : 'B';
        black = !black;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    bool black = true;
    for (int j = 0; j < m; ++j) {
      if (arr[i][j] == 'U') {
        arr[i][j] = black ? 'B' : 'W';
        arr[i + 1][j] = black ? 'W' : 'B';
        black = !black;
      }
    }
  }
  for (string s : arr) cout << s << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
