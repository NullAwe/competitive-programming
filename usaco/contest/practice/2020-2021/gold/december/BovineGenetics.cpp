#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;

const int MAX_N = 100001;
const string ACGT = "ACGT";

ll dp[MAX_N][4][4][4];

int main() {
  string str; cin >> str;
  int n = str.size();
  // Finds answer using dynamic programming:
  memset(dp, 0, sizeof(dp[0][0][0][0]) * MAX_N * 4 * 4 * 4);
  for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j)
    if (str[0] == '?' || str[0] == ACGT[j]) dp[0][i][j][j] = 1;
  for (int i = 1; i < n; ++i) {
    for (int end = 0; end < 4; ++end) {
      if (str[i] != '?' && str[i] != ACGT[end]) continue;
      for (int start = 0; start < 4; ++start) {
        for (int lStart = 0; lStart < 4; ++lStart) {
          for (int lEnd = 0; lEnd < 4; ++lEnd) {
            // We are able to continue the old segment:
            if (end != lEnd) {
              dp[i][lStart][start][end] += dp[i - 1][lStart][start][lEnd];
              dp[i][lStart][start][end] %= MOD;
            }
            // We are able to create a new segment:
            if (lStart == lEnd) {
              dp[i][start][end][end] += dp[i - 1][lStart][start][lEnd];
              dp[i][start][end][end] %= MOD;
            }
          }
        }
      }
    }
  }
  // Calculates answer:
  ll ans = 0;
  for (int ends = 0; ends < 4; ++ends) for (int mids = 0; mids < 4; ++mids)
    ans = (ans + dp[n - 1][ends][mids][ends]) % MOD;
  // Output:
  cout << ans << endl;
  return 0; 
}
