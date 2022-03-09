#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n, m; cin >> n >> m;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<pair<ll, ll>>> choices(n);
  vector<vector<int>> indices(n);
  for (int i = 0; i < m; ++i) {
    int e, t, p; cin >> e >> t >> p;
    choices[e - 1].push_back({t, p});
    indices[e - 1].push_back(i + 1);
  }
  ll base = 0;
  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    vector<vector<ll>> dp(indices[i].size() + 1, vector<ll>(101, INT_MAX)); dp[0][0] = 0;
    vector<vector<pair<ll, ll>>> hold(indices[i].size(), vector<pair<ll, ll>>(101));
    for (int index = 0; index < indices[i].size(); ++index) {
      pair<int, int> p = choices[i][index];
      int num = indices[i][index];
      ll time = p.first, percent = p.second;
      for (int j = 0; j < 101; ++j) {
        dp[index + 1][j] = dp[index][j];
        ll last = max(j - percent, 0LL);
        if (dp[index][last] == INT_MAX) continue;
        if (dp[index + 1][j] > time + dp[index][last]) {
          hold[index][j] = {num, percent};
          dp[index + 1][j] = time + dp[index][last];
        }
      }
    }
    if (base + dp[indices[i].size()][100] > arr[i] || dp[indices[i].size()][100] == INT_MAX) {
      cout << -1 << '\n';
      return;
    }
    ll val = 100, index;
    for (index = 0; index <= indices[i].size(); ++index) if (dp[index][100] == dp[indices[i].size()][100]) break;
    --index;
    while (val > 0) {
      if (hold[index][val].first != 0) ans.push_back(hold[index][val].first);
      val -= hold[index][val].second;
      --index;
    }
    base += dp[indices[i].size()][100];
  }
  cout << ans.size() << '\n';
  for (int num : ans) cout << num << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
