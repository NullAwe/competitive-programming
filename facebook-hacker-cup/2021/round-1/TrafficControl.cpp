#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n, m, a, b; cin >> n >> m >> a >> b;
    // Outputs "Impossible" for a special case:
    if (a < n + m - 1 || b < n + m - 1) {
      cout << "Case #" << i << ": Impossible" << endl;
      continue;
    }
    vector<vector<int>> grid(n, vector<int>(m, 1000));
    for (int j = 1; j < m - 1; ++j) for (int k = 0; k < n - 1; ++k)
      grid[k][j] = 1000;
    for (int j = 0; j < m; ++j) grid[n - 1][j] = 1;
    for (int j = 1; j < n; ++j) grid[j][0] = grid[j][m - 1] = 1;
    grid[0][0] = a - (n + m - 2);
    grid[0][m - 1] = b - (n + m - 2);
    // Output:
    cout << "Case #" << i << ": Possible" << endl;
    for (vector<int> row : grid) {
      for (int num : row) cout << num << " ";
      cout << endl;
    }
  }
  return 0;
}
