#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

ifstream in("daydayup.in");
ofstream out("daydayup.out");

int main() {
  int n; in >> n;
  vector<vector<pii>> groups(n - 1);
  vector<vector<bool>> has(n - 1, vector<bool>(n));
  int last = 0;
  for (int i = 0; i < n; ++i) {
    int cur = last;
    for (int j = i + 1; j < n; ++j) {
      while (true) {
        if (!has[cur][i] && !has[cur][j]) {
          groups[cur].push_back({i, j});
          has[cur][i] = has[cur][j] = true;
          if (i + 1 == j) last = cur;
          break;
        }
        ++cur, cur %= n - 1;
      }
    }
  }
  vector<vector<int>> vals(n, vector<int>(n));
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n / 2; ++j) {
      vals[groups[i][j].first][groups[i][j].second] = i * (n / 2) + j;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      out << vals[i][j] + 1 << ' ';
    }
    out << '\n';
  }
  return 0;
}
