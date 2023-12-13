#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int INF = 1000000000;

int main() {
  int n, k; cin >> n >> k;
  vector<vector<ll>> weights(n, vector<ll>(n));
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> weights[i][j];
  vector<pii> arr(n * n);
  for (int i = 0; i < n * n; ++i) cin >> arr[i].first >> arr[i].second;
  for (int i = 0; i < n * n; ++i) --arr[i].first, --arr[i].second;
  reverse(arr.begin(), arr.end());
  vector<vector<ll>> two(n, vector<ll>(n, INF));
  vector<ll> from1(n, INF);
  vector<ll> fromN(n, INF);
  int d1 = k / 2, d2 = k - d1;
  vector<vector<bool>> adj(n, vector<bool>(n));
  vector<ll> ans;
  for (int i = 0; i < n * n; ++i) {
    // answer query:
    ans.push_back(INF);
    for (int x = 0; x < n; ++x) {
      if (from1[x] == INF || fromN[x] == INF) continue;
      ans.back() = min(ans.back(), from1[x] + fromN[x]);
    }
    // update:
    int a = arr[i].first, b = arr[i].second;
    adj[a][b] = true;
    for (int y = 0; y < n; ++y) {
      if (!adj[b][y]) continue;
      two[a][y] = min(two[a][y], weights[a][b] + weights[b][y]);
    }
    for (int x = 0; x < n; ++x) {
      if (!adj[x][a]) continue;
      two[x][b] = min(two[x][b], weights[x][a] + weights[a][b]);
    }
    // solve f1:
    if (d1 == 1) {
      for (int x = 0; x < n; ++x) {
        // 1 -> x
        if (adj[0][x]) from1[x] = min(from1[x], weights[0][x]);
      }
    } else if (d1 == 2) {
      for (int x = 0; x < n; ++x) {
        // 1 -> b -> x
        if (adj[0][b] && adj[b][x]) from1[x] = min(from1[x], weights[0][b] + weights[b][x]);
        // 1 -> a -> x
        if (adj[0][a] && adj[a][x]) from1[x] = min(from1[x], weights[0][a] + weights[a][x]);
      }
    } else if (d1 == 3) {
      for (int x = 0; x < n; ++x) {
        // 1 -> b -> O -> x
        if (adj[0][b] && two[b][x] != INF) from1[x] = min(from1[x], weights[0][b] + two[b][x]);
        // 1 -> a -> b -> x
        if (adj[0][a] && adj[a][b] && adj[b][x]) from1[x] = min(from1[x], weights[0][a] + weights[a][b] + weights[b][x]);
        // 1 -> x -> a -> b
        if (adj[0][x] && adj[x][a] && adj[a][b]) from1[b] = min(from1[b], weights[0][x] + weights[x][a] + weights[a][b]);
      }
    } else {
      assert(d1 == 4);
      for (int x = 0; x < n; ++x) {
        if (a == 0) {
          // 1 -> b -> y -> O -> x
          for (int y = 0; y < n; ++y) {
            if (adj[0][b] && adj[b][y] && two[y][x] != INF)
              from1[x] = min(from1[x], weights[0][b] + weights[b][y] + two[y][x]);
          }
        }
        // 1 -> a -> b -> O -> x
        if (adj[0][a] && adj[a][b] && two[b][x] != INF) from1[x] = min(from1[x], weights[0][a] + weights[a][b] + two[b][x]);
        // 1 -> O -> a -> b -> x
        if (two[0][a] != INF && adj[a][b] && adj[b][x]) from1[x] = min(from1[x], two[0][a] + weights[a][b] + weights[b][x]);
        // 1 -> O -> x -> a -> b
        if (two[0][x] != INF && adj[x][a] && adj[a][b]) from1[b] = min(from1[b], two[0][x] + weights[x][a] + weights[a][b]);
      }
    }
    // solve fN:
    if (d2 == 1) {
      for (int x = 0; x < n; ++x) {
        // x -> N
        if (adj[x][n - 1]) fromN[x] = min(fromN[x], weights[x][n - 1]);
      }
    } else if (d2 == 2) {
      for (int x = 0; x < n; ++x) {
        // x -> a -> N
        if (adj[x][a] && adj[a][n - 1]) fromN[x] = min(fromN[x], weights[x][a] + weights[a][n - 1]);
        // x -> b -> N
        if (adj[x][b] && adj[b][n - 1]) fromN[x] = min(fromN[x], weights[x][b] + weights[b][n - 1]);
      }
    } else if (d2 == 3) {
      for (int x = 0; x < n; ++x) {
        // x -> O -> a -> N
        if (two[x][a] != INF && adj[a][n - 1]) fromN[x] = min(fromN[x], two[x][a] + weights[a][n - 1]);
        // x -> a -> b -> N
        if (adj[x][a] && adj[a][b] && adj[b][n - 1]) fromN[x] = min(fromN[x], weights[x][a] + weights[a][b] + weights[b][n - 1]);
        // a -> b -> x -> N
        if (adj[a][b] && adj[b][x] && adj[x][n - 1]) fromN[a] = min(fromN[a], weights[a][b] + weights[b][x] + weights[x][n - 1]);
      }
    } else {
      assert(d2 == 4);
      for (int x = 0; x < n; ++x) {
        if (b == n - 1) {
          // x -> O -> y -> a -> N
          for (int y = 0; y < n; ++y) {
            if (two[x][y] != INF && adj[y][a] && adj[a][n - 1])
              fromN[x] = min(fromN[x], two[x][y] + weights[y][a] + weights[a][n - 1]);
          }
        }
        // x -> O -> a -> b -> N
        if (two[x][a] != INF && adj[a][b] && adj[b][n - 1])
          fromN[x] = min(fromN[x], two[x][a] + weights[a][b] + weights[b][n - 1]);
        // x -> a -> b -> O -> N
        if (adj[x][a] && adj[a][b] && two[b][n - 1] != INF)
          fromN[x] = min(fromN[x], weights[x][a] + weights[a][b] + two[b][n - 1]);
        // a -> b -> x -> O -> N
        if (adj[a][b] && adj[b][x] && two[x][n - 1] != INF)
          fromN[a] = min(fromN[a], weights[a][b] + weights[b][x] + two[x][n - 1]);
      }
    }
  }
  reverse(ans.begin(), ans.end());
  for (ll num : ans) {
    cout << (num == INF ? -1 : num) << '\n';
  }
  return 0;
}