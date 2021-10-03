#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m, k; cin >> n >> m >> k;
  vector<vector<int>> arr(n, vector<int>(m));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> arr[i][j];
  for (int i = 0; i < k; ++i) {
    // Finds answer by simulating:
    int x = 0, y; cin >> y; --y;
    while (x < n) {
      int num = arr[x][y];
      arr[x][y] = 2;
      if (num == 1) ++y;
      else if (num == 3) --y;
      else ++x;
    }
    // Output:
    cout << y + 1 << ' ';
  }
  return 0;
}
