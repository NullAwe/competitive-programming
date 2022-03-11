#include <bits/stdc++.h>
using namespace std;

void output(int a, int b, int c, int d) {
  cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
}

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> arr(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    string str; cin >> str;
    for (int j = 0; j < m; ++j) arr[i][j] = str[j] - '0';
  }
  if (arr[0][0] == 1) {
    cout << -1 << '\n';
    return;
  }
  cout << n * m << '\n';
  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      if (!arr[i][j]) output(i + 1, j + 1, i + 1, j + 1);
      else if (j == 0) output(i, j + 1, i + 1, j + 1);
      else output(i + 1, j, i + 1, j + 1);
    }
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
