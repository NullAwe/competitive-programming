#include <bits/stdc++.h>
using namespace std;
 
const int oo = 2147483647;
 
int main() {
  int n, w;
  cin >> n >> w;
  vector<int> weights(n);
  for (int i = 0; i < n; ++i) cin >> weights[i];
  vector<pair<int, int>> memo(1 << n, {oo, oo});
  memo[0] = {0, 0};
  for (int i = 1; i < (1 << n); ++i) {
    for (int j = 0; j < n; ++j) {
      if (!(i & (1 << j))) continue;
      int mask = i & ~(1 << j);
      pair<int, int> p = memo[mask];
      if (p.second + weights[j] <= w) p.second += weights[j];
      else {
        ++p.first;
        p.second = weights[j];
      }
      if (p.first > memo[i].first) continue;
      if (p.first < memo[i].first || p.second < memo[i].second) memo[i] = p;
    }
  }
  cout << memo[(1 << n) - 1].first + 1;
  return 0;
}
