#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n;
  cin >> n;
  vector<int> coins(n);
  for (int i = 0; i < n; ++i) cin >> coins[i];
  vector<unordered_set<int>> memo(n + 1, unordered_set<int>());
  for (int i = 1; i <= n; ++i) {
    memo[i] = memo[i - 1];
    for (int num : memo[i - 1]) {
      int sum = num + coins[i - 1];
      if (!memo[i].count(sum)) memo[i].insert(sum);
    }
    if (!memo[i].count(coins[i - 1])) memo[i].insert(coins[i - 1]);
  }
  vector<int> sums(memo[n].size());
  int i = -1;
  for (int num : memo[n]) sums[++i] = num;
  sort(sums.begin(), sums.end());
  cout << sums.size() << "\n";
  for (int sum : sums) cout << sum << ' ';
  return 0;
}
