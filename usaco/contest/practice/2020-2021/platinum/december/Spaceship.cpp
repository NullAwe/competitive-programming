#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MOD = 1e9 + 7;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, k, q; cin >> n >> k >> q;
  vector<string> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<pii> eds(q), fcd(q);
  for (int i = 0; i < q; ++i) {
    int sb, s, eb, e; cin >> sb >> s >> eb >> e; --sb, --s, --eb, --e;
    eds[i] = {s, e}, fcd[i] = {sb, eb};
  }
  int dp[k][n + q][n + q];
  for (int i = 0; i < k; ++i) for (int j = 0; j < n + q; ++j) for (int l = 0; l < n + q; ++l)
    dp[i][j][l] = 0;
  for (int i = 0; i < n; ++i) dp[0][i][i] = 1;
  for (int i = 0; i < q; ++i) if (!max(fcd[i].first, fcd[i].second))
    if (fcd[i].first == fcd[i].second && eds[i].first == eds[i].second) ++dp[0][i + n][i + n];
  for (int mx = 1; mx < k; ++mx) {
    for (int i = 0; i < n + q; ++i) for (int j = 0; j < n + q; ++j) dp[mx][i][j] = dp[mx - 1][i][j];
    for (int mid = 0; mid < n; ++mid) {
      vector<int> w1(n + q);
      for (int i = 0; i < n + q; ++i) for (int bef = 0; bef < n; ++bef)
        if (arr[bef][mid] == '1' && (i < n || fcd[i - n].first < mx)) w1[i] = (w1[i] + dp[mx - 1][i][bef]) % MOD;
      vector<int> w2(n + q);
      for (int i = 0; i < n + q; ++i) for (int aft = 0; aft < n; ++aft)
        if (arr[mid][aft] == '1' && (i < n || fcd[i - n].second < mx)) w2[i] = (w2[i] + dp[mx - 1][aft][i]) % MOD;
      for (int i = 0; i < n + q; ++i) for (int j = 0; j < n + q; ++j)
        dp[mx][i][j] = (dp[mx][i][j] + (ll) w1[i] * w2[j] % MOD) % MOD;
      for (int i = 0; i < n + q; ++i) dp[mx][i][mid] = (dp[mx][i][mid] + w1[i]) % MOD;
      for (int i = 0; i < n + q; ++i) dp[mx][mid][i] = (dp[mx][mid][i] + w2[i]) % MOD;
      for (int i = 0; i < q; ++i) if (mx > fcd[i].first && arr[eds[i].first][mid] == '1') {
        for (int j = 0; j < n + q; ++j) dp[mx][i + n][j] = (dp[mx][i + n][j] + w2[j]) % MOD;
        ++dp[mx][i + n][mid];
      }
      for (int i = 0; i < q; ++i) if (mx > fcd[i].second && arr[mid][eds[i].second] == '1') {
        for (int j = 0; j < n + q; ++j) dp[mx][j][i + n] = (dp[mx][j][i + n] + w1[j]) % MOD;
        ++dp[mx][mid][i + n];
      }
      for (int i = 0; i < q; ++i) if (mx > max(fcd[i].first, fcd[i].second)) {
        if (arr[eds[i].first][mid] == '1' && arr[mid][eds[i].second] == '1') {
          ++dp[mx][i + n][i + n];
        }
      }
      ++dp[mx][mid][mid];
    }
    for (int i = 0; i < q; ++i) {
      if (mx == fcd[i].first) {
        for (int mid = 0; mid < n; ++mid) {
          if (arr[eds[i].first][mid] == '0') continue;
          for (int j = 0; j < n; ++j) dp[mx][i + n][j] = (dp[mx][i + n][j] + dp[mx - 1][mid][j]) % MOD;
        }
      }
      if (mx == fcd[i].second) {
        for (int mid = 0; mid < n; ++mid) {
          if (arr[mid][eds[i].second] == '0') continue;
          for (int j = 0; j < n; ++j) dp[mx][j][i + n] = (dp[mx][j][i + n] + dp[mx - 1][j][mid]) % MOD;
        }
      }
      if (mx == max(fcd[i].first, fcd[i].second)) {
        if (fcd[i].first == fcd[i].second) {
          if (eds[i].first == eds[i].second) ++dp[mx][i + n][i + n];
        } else if (fcd[i].first > fcd[i].second) {
          for (int j = 0; j < n; ++j) if (arr[eds[i].first][j] == '1')
            dp[mx][i + n][i + n] = (dp[mx][i + n][i + n] + dp[mx - 1][j][i + n]) % MOD;
          if (arr[eds[i].first][eds[i].second] == '1') ++dp[mx][i + n][i + n];
        } else {
          for (int j = 0; j < n; ++j) if (arr[j][eds[i].second] == '1')
            dp[mx][i + n][i + n] = (dp[mx][i + n][i + n] + dp[mx - 1][i + n][j]) % MOD;
          if (arr[eds[i].first][eds[i].second] == '1') ++dp[mx][i + n][i + n];
        }
      }
    }
  }
  for (int i = 0; i < q; ++i) cout << dp[k - 1][i + n][i + n] % MOD << '\n';
  return 0;
}
