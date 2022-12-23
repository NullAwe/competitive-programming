#include <bits/stdc++.h>
using namespace std;

const int INF = 5e8;

bool adj[40][40];
int n, m;
int start, ed;
vector<int> costs;
vector<vector<bool>> can(2, vector<bool>(1 << 20));
vector<vector<int>> dp(2, vector<int>(1 << 20, INF));

void check(bool add) {
  int until = max(min((add + 1) * 20, m) - add * 20, 0);
  for (int i = 0; i < (1 << until); ++i) {
    bool yes = true;
    for (int j = add * 20; j < (add + 1) * 20; ++j) {
      for (int k = j; k < (add + 1) * 20; ++k) {
        if (!adj[j][k]) continue;
        if (!(i & (1 << (j - add * 20))) && !(i & (1 << (k - add * 20)))) yes = false;
      }
    }
    if (add * 20 <= start && start < (add + 1) * 20) {
      if (!(i & (1 << (start - add * 20)))) yes = false;
    }
    if (add * 20 <= ed && ed < (add + 1) * 20) {
      if (!(i & (1 << (ed - add * 20)))) yes = false;
    }
    can[add][i] = yes;
  }
}

void iter() {
  int until = min(20, m);
  for (int i = 0; i < (1 << until); ++i) {
    if (!can[0][i]) continue;
    int cost = 0;
    for (int j = 0; j < until; ++j) if (i & (1 << j)) cost += costs[j];
    dp[0][i] = cost;
  }
  until = max(min(20, m - 20), 0);
  for (int i = 0; i < (1 << until); ++i) {
    if (!can[1][i]) continue;
    int cost = 0;
    for (int j = 0; j < until; ++j) if (i & (1 << j)) cost += costs[j + 20];
    dp[1][i] = cost;
  }
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < (1 << 20); ++j) {
      if ((j & (1 << i))) continue;
      int with = j | (1 << i);
      dp[1][j] = min(dp[1][j], dp[1][with]);
    }
  }
}

int main() {
  cin >> n >> m;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) --arr[i];
  start = arr[0], ed = arr.back();
  for (int i = 1; i < n; ++i) adj[arr[i]][arr[i - 1]] = adj[arr[i - 1]][arr[i]] = 1;
  costs.resize(m);
  for (int i = 0; i < m; ++i) cin >> costs[i];
  check(0), check(1), iter();
  int until = min(20, m);
  int ans = 0; for (int num : costs) ans += num;
  for (int i = 0; i < (1 << until); ++i) {
    if (!can[0][i]) continue;
    int must = 0;
    for (int j = 0; j < 20; ++j) {
      for (int k = 20; k < 40; ++k) {
        if (!adj[j][k]) continue;
        if (!(i & (1 << j))) must |= (1 << (k - 20));
      }
    }
    ans = min(ans, dp[0][i] + dp[1][must]);
  }
  cout << ans << '\n';
  return 0;
}

