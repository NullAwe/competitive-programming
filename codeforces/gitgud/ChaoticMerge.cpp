#include <iostream>
#include <vector>
using namespace std;

#define ll long long

const int MOD = 998244353;

int main() {
  string s, t; cin >> s >> t;
  int n = s.size(), m = t.size();
  vector<vector<vector<int>>> memo(n + 1, vector<vector<int>>(m + 1, vector<int>(27)));
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) memo[i][j][26] = 1;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i) {
        int sv = s[i - 1] - 'a';
        for (int k = 0; k < 27; ++k) if (sv != k) memo[i][j][sv] = (memo[i][j][sv] + memo[i - 1][j][k]) % MOD;
      }
      if (j) {
        int tv = t[j - 1] - 'a';
        for (int k = 0; k < 27; ++k) if (tv != k) memo[i][j][tv] = (memo[i][j][tv] + memo[i][j - 1][k]) % MOD;
      }
    }
  }
  int sum = 0;
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) for (int k = 0; k < 27; ++k) sum = (sum + memo[i][j][k]) % MOD;
  sum -= (m + 1) * (n + 1);
  for (int i = 0; i < n; ++i) {
    sum = (sum - m - 1 + MOD) % MOD;
    for (int j = i + 1; j < n; ++j) {
      if (s[j] == s[j - 1]) break;
      sum = (sum - m - 1 + MOD) % MOD;
    }
  }
  for (int i = 0; i < m; ++i) {
    sum = (sum - n - 1 + MOD) % MOD;
    for (int j = i + 1; j < m; ++j) {
      if (t[j] == t[j - 1]) break;
      sum = (sum - n - 1 + MOD) % MOD;
    }
  }
  cout << sum << '\n';
  return 0;
}
