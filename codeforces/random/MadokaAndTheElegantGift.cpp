#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> arr(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    string str; cin >> str;
    for (int j = 0; j < m; ++j) arr[i][j] = str[j] - '0';
  }
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < m - 1; ++j) {
      if (arr[i][j] + arr[i + 1][j] + arr[i][j + 1] + arr[i + 1][j + 1] == 3) {
        cout << "NO\n";
        return;
      }
    }
  }
  cout << "YES\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
