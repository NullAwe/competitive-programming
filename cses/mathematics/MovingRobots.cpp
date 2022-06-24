#include <bits/stdc++.h>
using namespace std;

const vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};

int main() {
  int x; cin >> x;
  vector<vector<int>> ms(8, vector<int>(8, 4));
  for (int i = 0; i < 8; ++i) ms[i][0] = ms[i][7] = ms[0][i] = ms[7][i] = 3;
  ms[0][0] = ms[0][7] = ms[7][0] = ms[7][7] = 2;
  vector<vector<double>> p(8, vector<double>(8, 1));
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      vector<vector<double>> dp(8, vector<double>(8)); dp[i][j] = 1;
      for (int iter = 0; iter < x; ++iter) {
        vector<vector<double>> ndp(8, vector<double>(8));
        for (int r = 0; r < 8; ++r) {
          for (int c = 0; c < 8; ++c) {
            for (int dir = 0; dir < 4; ++dir) {
              int nr = r + dx[dir], nc = c + dy[dir];
              if (nr < 0 || nc < 0 || nr > 7 || nc > 7) continue;
              ndp[r][c] += dp[nr][nc] / ms[nr][nc];
            }
          }
        }
        dp = ndp;
      }
      for (int r = 0; r < 8; ++r) for (int c = 0; c < 8; ++c) p[r][c] *= 1 - dp[r][c];
    }
  }
  double ans = 0; for (vector<double> r : p) for (double d : r) ans += d;
  cout << fixed << setprecision(6) << ans << '\n';
}
