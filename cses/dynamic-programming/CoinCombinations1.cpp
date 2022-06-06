#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
const int oo = 2147483647;
 
int main() {
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int i = 0; i < n; ++i) cin >> coins[i];
  vector<ll> memo(x + 1);
  memo[0] = 1;
  for (int i = 1; i <= x; ++i) {
    for (int coin : coins) {
      if (i - coin < 0) continue;
      memo[i] += memo[i - coin];
    }
    memo[i] %= 1000000007;
  }
  cout << (memo[x] == oo ? -1 : memo[x]) << "\n";
  return 0;
}
