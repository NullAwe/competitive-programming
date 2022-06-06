#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 1000000007;
 
int main() {
  int n;
  cin >> n;
  vector<string> board(n);
  for (int i = 0; i < n; ++i) cin >> board[i];
  vector<vector<int>> memo(n, vector<int>(n));
  if (board[0][0] == '*') {
    cout << "0\n";
    return 0;
  }
  memo[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if ((i == 0 && j == 0) || board[i][j] == '*') continue;
      if (i == 0) memo[i][j] = memo[i][j - 1];
      else if (j == 0) memo[i][j] = memo[i - 1][j];
      else memo[i][j] = memo[i][j - 1] + memo[i - 1][j];
      memo[i][j] %= MOD;
    }
  }
  cout << memo[n - 1][n - 1] << "\n";
  return 0;
}
