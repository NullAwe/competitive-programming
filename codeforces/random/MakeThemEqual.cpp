#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
  vector<int> c(n); for (int i = 0; i < n; ++i) cin >> c[i];
  vector<int> ops(1001, INT_MAX); ops[1] = 0;
  for (int i = 1; i < 1001; ++i) {
    for (int j = 1; j <= i; ++j) {
      int next = i + i / j;
      if (next < 1001) ops[next] = min(ops[next], ops[i] + 1);
    }
  }
  int total = 0; for (int num : b) total += ops[num];
  int sz = min(total, k) + 1;
  vector<int> dp(sz);
  for (int i = 0; i < n; ++i) {
    int op = ops[b[i]], cost = c[i];
    for (int from = sz - 1 - op; from >= 0; --from) dp[from + op] = max(dp[from + op], dp[from] + cost);
  }
  cout << dp[sz - 1] << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
