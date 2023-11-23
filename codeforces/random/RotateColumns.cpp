#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void solve() {
  int n, m; cin >> n >> m;
  vector<int> dp(2 << n);
  vector<vector<int>> arr(n, vector<int>(m));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> arr[i][j];
  if (m > n) {
    vector<pii> mxs(m);
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) mxs[j].first = max(mxs[j].first, arr[i][j]);
    for (int j = 0; j < m; ++j) mxs[j].second = j;
    sort(mxs.begin(), mxs.end());
    reverse(mxs.begin(), mxs.end());
    vector<vector<int>> narr(n, vector<int>(n));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) narr[i][j] = arr[i][mxs[j].second];
    arr = narr;
    m = n;
  }
  for (int i = 0; i < m; ++i) {
    vector<int> ndp = dp;
    vector<int> mdp(2 << n);
    for (int j = 1; j < (2 << n); ++j) {
      int sum = 0;
      for (int k = 0; k < n; ++k) if (j & (1 << k)) sum += arr[k][i];
      int tmp = j;
      for (int k = 0; k < n; ++k) {
        mdp[tmp] = max(mdp[tmp], sum);
        bool d = tmp & 1;
        tmp >>= 1;
        if (d) tmp |= 1 << (n - 1);
      }
    }
    for (int j = 1; j < (2 << n); ++j) for (int k = j; k > 0; k = (k - 1) & j)
      ndp[j] = max(ndp[j], dp[j ^ k] + mdp[k]);
    dp = ndp;
  }
  cout << dp.back() << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}