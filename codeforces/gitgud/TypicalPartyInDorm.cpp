#include <iostream>
#include <vector>
#include <utility>
using namespace std;

#define ll long long

const int MOD = 998244353;

int main() {
  int n; cin >> n;
  string str; cin >> str;
  vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n));
  for (int i = 0; i < n; ++i) if (str[i] == '?') dp[i][i].first = 1;
  for (int i = 1; i < n; ++i) {
    if (str[i - 1] == '?' && str[i] == '?') dp[i - 1][i].first = 1;
    else if (str[i - 1] == '?') dp[i - 1][i].second = (1 << (str[i] - 'a'));
    else if (str[i] == '?') dp[i - 1][i].second = (1 << (str[i - 1] - 'a'));
    else if (str[i - 1] != str[i]) dp[i - 1][i] = {-1, -1};
  }
  for (int len = 3; len <= n; ++len) {
    for (int start = 0; start + len <= n; ++start) {
      int end = start + len - 1;
      dp[start][end] = dp[start + 1][end - 1];
      if (dp[start][end].first < 0) continue;
      if (str[start] == '?' && str[end] == '?') ++dp[start][end].first;
      else if (str[start] == '?') dp[start][end].second |= (1 << (str[end] - 'a'));
      else if (str[end] == '?') dp[start][end].second |= (1 << (str[start] - 'a'));
      else if (str[start] != str[end]) dp[start][end] = {-1, -1};
    }
  }
  vector<int> free(n + 1); for (int i = 0; i < n; ++i) free[i + 1] = free[i] + (str[i] == '?');
  vector<vector<int>> tracker(1 << 17);
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      if (dp[i][j].first < 0) continue;
      tracker[dp[i][j].second].push_back(dp[i][j].first + free[n] - free[j + 1] + free[i]);
    }
  }
  vector<vector<int>> powers(18, vector<int>(n + 1));
  for (int i = 1; i < 18; ++i) {
    powers[i][0] = 1;
    for (int j = 1; j <= n; ++j) powers[i][j] = (int) ((ll) powers[i][j - 1] * i % MOD);
  }
  vector<vector<int>> vals(18, vector<int>(1 << 17));
  for (int i = 1; i < 18; ++i)
    for (int j = 0; j < (1 << 17); ++j)
      for (int exp : tracker[j])
        vals[i][j] = (vals[i][j] + powers[i][exp]) % MOD;
  vector<vector<int>> dp2(18, vector<int>(1 << 17));
  for (int i = 1; i < 18; ++i) {
    for (int j = 0; j < (1 << 17); ++j) dp2[i][j] = vals[i][j];
    for (int j = 0; j < 17; ++j) for (int mask = 0; mask < (1 << 17); ++mask)
      if (mask & (1 << j)) dp2[i][mask] = (dp2[i][mask] + dp2[i][mask ^ (1 << j)]) % MOD;
  }
  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    string str; cin >> str;
    int size = str.size(), mask = 0;
    for (int i = 0; i < size; ++i) mask |= 1 << (str[i] - 'a');
    cout << dp2[size][mask] << '\n';
  }
  return 0;
}
