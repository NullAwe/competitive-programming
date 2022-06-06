#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX_N = 1e6 + 1;

vector<pair<int, int>> dp(MAX_N);

void solve() {
  int n; cin >> n;
  cout << (dp[n].first + dp[n].second) % MOD << '\n';
}

int main() {
  dp[1] = {1, 1};
  for (int i = 2; i < MAX_N; ++i)
    dp[i] = {(2 * dp[i - 1].first % MOD + dp[i - 1].second) % MOD, (int) ((dp[i - 1].first + (long long) 4 * dp[i - 1].second % MOD) % MOD)};
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
