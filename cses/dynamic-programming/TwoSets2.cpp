#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
int main() {
  int n;
  cin >> n;
  if (n % 4 == 1 || n % 4 == 2) {
    cout << 0 << "\n";
    return 0;
  }
  int x = (n * (n + 1)) / 4;
  vector<vector<int>> memo(n + 1, vector<int>(x + 1));
  for (int i = 0; i <= n; ++i) memo[i][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= x; ++j) {
      memo[i][j] = memo[i - 1][j];
      int l = j - i;
      if (l >= 0) memo[i][j] += memo[i - 1][l];
      memo[i][j] %= 1000000007;
    }
  }
  cout << ((((ll) memo[n][x]) * 500000004) % 1000000007) << "\n";
  return 0;
}
