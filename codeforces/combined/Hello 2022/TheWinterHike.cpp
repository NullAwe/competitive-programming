#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<vector<ll>> snow(2 * n, vector<ll>(2 * n));
  for (int i = 0; i < 2 * n; ++i) for (int j = 0; j < 2 * n; ++j) cin >> snow[i][j];
  ll cost = 0;
  for (int i = n; i < 2 * n; ++i) for (int j = n; j < 2 * n; ++j) cost += snow[i][j], snow[i][j] = 0;
  vector<vector<ll>> dists(2 * n, vector<ll>(2 * n, -1));
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) dists[i][j] = 0;
  vector<pair<int, int>> inits;
  inits.push_back({0, n});
  inits.push_back({0, 2 * n - 1});
  inits.push_back({n - 1, n});
  inits.push_back({n - 1, 2 * n - 1});
  inits.push_back({n, 0});
  inits.push_back({n, n - 1});
  inits.push_back({2 * n - 1, 0});
  inits.push_back({2 * n - 1, n - 1});
  set<pair<int, pair<int, int>>> q;
  for (pair<int, int> init : inits) {
    dists[init.first][init.second] = snow[init.first][init.second];
    q.insert({dists[init.first][init.second], {init.first, init.second}});
  }
  while (q.size()) {
    pair<int, int> node = (*q.begin()).second; q.erase(q.begin());
    for (int i = -1; i < 2; ++i) {
      for (int j = -1; j < 2; ++j) {
        if (i && j) continue;
        int x = (node.first + i + 2 * n) % (2 * n);
        int y = (node.second + j + 2 * n) % (2 * n);
        if (dists[x][y] >= 0) continue;
        dists[x][y] = dists[node.first][node.second] + snow[x][y];
        q.insert({dists[x][y], {x, y}});
      }
    }
  }
  // Output:
  cout << cost + dists[n][n] << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
