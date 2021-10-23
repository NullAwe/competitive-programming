#include <bits/stdc++.h>
using namespace std;

vector<int> dx = {0, 1}, dy = {1, 0};

void modify(vector<int>& t, int n, int p, int value) {
  for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
}

int query(vector<int>& t, int n, int l, int r) {
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res = max(res, t[l++]);
    if (r & 1) res = max(res, t[--r]);
  }
  return res;
}

void fill(int x, int y, int val, vector<string>& grid, vector<vector<int>>& f) {
  if (x < 0 || y < 0 || x >= grid.size() || y >= grid[x].size()) return;
  if (grid[x][y] == 'X' || f[x][y] > 0) return;
  f[x][y] = val;
  for (int i = 0; i < dx.size(); ++i) fill(x + dx[i], y + dy[i], val, grid, f);
}

int main() {
  int n, m; cin >> n >> m;
  vector<string> grid(n); for (int i = 0; i < n; ++i) cin >> grid[i];
  vector<vector<int>> f(n, vector<int>(m));
  int id = 1;
  for (int i = 0; i < m; ++i)
    if (grid[0][i] == '.' && f[0][i] == 0) fill(0, i, id++, grid, f);
  for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j)
    if (grid[j][i] == '.' && f[j][i] == 0) fill(j, i, id++, grid, f);
  vector<int> has(m);
  for (int i = 1; i < m; ++i) for (int j = 1; j < n; ++j)
    if (grid[j][i] == 'X' && grid[j - 1][i] == 'X' && grid[j][i - 1] == 'X') {
      has[i] = true;
      break;
    }
  vector<int> maxCol(m);
  for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j)
    maxCol[i] = max(maxCol[i], f[j][i]);
  vector<int> mct(2 * m), mcr(2 * m), mch(2 * m);
  for (int i = 0; i < m; ++i) modify(mct, m, i, maxCol[i]);
  for (int i = 0; i < m; ++i) modify(mcr, m, i, f[0][i]);
  for (int i = 0; i < m; ++i) modify(mch, m, i, has[i]);
  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a;
    int exitMax = max(maxCol[a], query(mcr, m, a, b));
    int gridMax = query(mct, m, a, b);
    // Output:
    if (gridMax > exitMax || query(mch, m, a + 1, b)) cout << "NO" << endl;
    else cout << "YES" << endl;
  }
  return 0;
}
