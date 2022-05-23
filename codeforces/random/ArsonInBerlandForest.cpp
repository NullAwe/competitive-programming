#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> forest;
vector<vector<int>> px;

bool possible(int t) {
  vector<vector<bool>> avail(n, vector<bool>(m));
  for (int i = t * 2 + 1; i <= n; ++i) for (int j = t * 2 + 1; j <= m; ++j)
    if (px[i][j] - px[i - t * 2 - 1][j] - px[i][j - t * 2 - 1] +
        px[i - t * 2 - 1][j - t * 2 - 1] == (t * 2 + 1) * (t * 2 + 1))
      avail[i - t * 2 - 1][j - t * 2 - 1] = true;
  vector<vector<int>> pa(n + 1, vector<int>(m + 1));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    pa[i + 1][j + 1] = pa[i + 1][j] + pa[i][j + 1] - pa[i][j] + avail[i][j];
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
    if (forest[i - 1][j - 1] == 'X' &&
        !(pa[i][j] - pa[max(i - t * 2 - 1, 0)][j] - pa[i][max(j - t * 2 - 1, 0)] +
        pa[max(i - t * 2 - 1, 0)][max(j - t * 2 - 1, 0)])) return false;
  return true;
}

int main() {
  cin >> n >> m;
  forest = vector<string>(n); for (int i = 0; i < n; ++i) cin >> forest[i];
  px = vector<vector<int>>(n + 1, vector<int>(m + 1));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    px[i + 1][j + 1] = px[i + 1][j] + px[i][j + 1] - px[i][j] + (forest[i][j] == 'X');
  int lo = 0, hi = min(n, m);
  while (lo < hi - 1) {
    int mid = (lo + hi) >> 1;
    if (possible(mid)) lo = mid;
    else hi = mid;
  }
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) forest[i][j] = '.';
  cout << lo << '\n';
  for (int i = lo * 2 + 1; i <= n; ++i) for (int j = lo * 2 + 1; j <= m; ++j)
    if (px[i][j] - px[i - lo * 2 - 1][j] - px[i][j - lo * 2 - 1] +
        px[i - lo * 2 - 1][j - lo * 2 - 1] == (lo * 2 + 1) * (lo * 2 + 1))
      forest[i - lo - 1][j - lo - 1] = 'X';
  for (string str : forest) cout << str << '\n';
  return 0;
}
