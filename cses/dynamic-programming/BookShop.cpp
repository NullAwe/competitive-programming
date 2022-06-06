#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n, x;
  cin >> n >> x;
  vector<int> prices(n), pages(n);
  for (int i = 0; i < n; ++i) cin >> prices[i];
  for (int i = 0; i < n; ++i) cin >> pages[i];
  vector<vector<int>> memo(n + 1, vector<int>(x + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= x; ++j) {
      memo[i][j] = memo[i - 1][j];
      int l = j - prices[i - 1];
      if (l >= 0) memo[i][j] = max(memo[i][j], memo[i - 1][l] + pages[i - 1]);
    }
  }
  cout << memo[n][x] << "\n";
  return 0;
}
