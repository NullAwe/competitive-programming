#include <bits/stdc++.h>
using namespace std;

int sq(int x) { return x * x; }

int dp(int x, int y, vector<vector<int>>& memo, vector<pair<int, int>>& f, vector<pair<int, int>>& b) {
  if (x >= f.size() || y >= b.size()) return INT_MAX;
  int dist = sq(f[x].first - b[y].first) + sq(f[x].second - b[y].second);
  if (x == f.size() - 1 && y == b.size() - 1) return dist;
  if (memo[x][y] < INT_MAX) return memo[x][y];
  memo[x][y] = dist + min(dp(x + 1, y, memo, f, b), min(dp(x, y + 1, memo, f, b), dp(x + 1, y + 1, memo, f, b)));
  if ((x | y) == 0) memo[x][y] -= dist;
  return memo[x][y];
}

int main() {
  ifstream in("radio.in");
  ofstream out("radio.out");
  int n, m; in >> n >> m;
  vector<pair<int, int>> f(n + 1), b(m + 1);
  int fx, fy, bx, by; in >> fx >> fy >> bx >> by;
  f[0] = {fx, fy}; b[0] = {bx, by};
  string d1, d2; in >> d1 >> d2;
  for (int i = 1; i <= n; ++i) {
    char dir = d1[i - 1];
    int x = 0, y = 0;
    if (dir == 'N') y = 1;
    else if (dir == 'E') x = 1;
    else if (dir == 'S') y = -1;
    else x = -1;
    f[i] = {f[i - 1].first + x, f[i - 1].second + y};
  }
  for (int i = 1; i <= m; ++i) {
    char dir = d2[i - 1];
    int x = 0, y = 0;
    if (dir == 'N') y = 1;
    else if (dir == 'E') x = 1;
    else if (dir == 'S') y = -1;
    else x = -1;
    b[i] = {b[i - 1].first + x, b[i - 1].second + y};
  }
  vector<vector<int>> memo(n + 1, vector<int>(m + 1, INT_MAX));
  // Output:
  out << dp(0, 0, memo, f, b) << endl;
  return 0;
}
