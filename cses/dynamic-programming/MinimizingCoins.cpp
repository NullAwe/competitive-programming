#include <bits/stdc++.h>
using namespace std;
 
const int oo = 2147483647;
 
int main() {
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int i = 0; i < n; ++i) cin >> coins[i];
  vector<int> memo(x + 1, oo);
  memo[0] = 0;
  for (int i = 1; i <= x; ++i) {
    int m = oo;
    for (int coin : coins) {
      if (i - coin < 0) continue;
      int get = memo[i - coin];
      if (get == oo) continue;
      m = min(m, get + 1);
    }
    memo[i] = m;
  }
  cout << (memo[x] == oo ? -1 : memo[x]) << "\n";
  return 0;
}
