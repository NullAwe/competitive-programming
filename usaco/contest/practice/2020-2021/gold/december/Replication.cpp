#include <bits/stdc++.h>
using namespace std;

#define ll long long

const vector<int> dx = {0, 0, -1, 1}, dy = {-1, 1, 0, 0};

int main() {
  ll n, d; cin >> n >> d;
  vector<string> grid(n); for (int i = 0; i < n; ++i) cin >> grid[i];
  queue<pair<int, int>> q;
  // BFS to find distance from nearest rock:
  vector<vector<int>> rockDists(n, vector<int>(n, -1));
  vector<vector<bool>> vis(n, vector<bool>(n, false));
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    if (grid[i][j] == '#') {
      q.push({i, j});
      rockDists[i][j] = 0;
      vis[i][j] = true;
    }
  }
  while (q.size()) {
    pair<int, int> node = q.front(); q.pop();
    for (int i = 0; i < dx.size(); ++i) {
      int x = node.first + dx[i], y = node.second + dy[i];
      if (x < 0 || y < 0 || x >= n || y >= n || grid[x][y] == '#' || vis[x][y]) continue;
      rockDists[x][y] = rockDists[node.first][node.second] + 1;
      vis[x][y] = true;
      q.push({x, y});
    }
  }
  // BFS to find possible centers:
  queue<pair<pair<int, int>, int>> q2;
  vector<pair<int, int>> centers[n + 5];
  vis = vector<vector<bool>>(n, vector<bool>(n, false));
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    if (grid[i][j] == 'S') {
      q2.push({{i, j}, 0});
      centers[rockDists[i][j]].push_back({i, j});
      vis[i][j] = true;
    }
  }
  while (q2.size()) {
    pair<pair<int, int>, int> node = q2.front(); q2.pop();
    if (node.second / d >= rockDists[node.first.first][node.first.second]) continue;
    for (int i = 0; i < dx.size(); ++i) {
      int x = node.first.first + dx[i], y = node.first.second + dy[i];
      if (x < 0 || y < 0 || x >= n || y >= n || grid[x][y] == '#' || vis[x][y]) continue;
      if (node.second / d >= rockDists[x][y]) continue;
      centers[rockDists[x][y]].push_back({x, y});
      vis[x][y] = true;
      q2.push({{x, y}, node.second + 1});
    }
  }
  // BFS to find answer:
  vis = vector<vector<bool>>(n, vector<bool>(n, false));
  for (pair<int, int> center : centers[n + 4]) {
    q.push({center.first, center.second});
    vis[center.first][center.second] = true;
  }
  int ans = 0;
  for (int i = n + 4; i > 0; --i) {
    queue<pair<int, int>> next;
    for (pair<int, int> center : centers[i - 1]) {
      if (vis[center.first][center.second]) continue;
      next.push(center);
      vis[center.first][center.second] = true;
    }
    while (q.size()) {
      pair<int, int> node = q.front(); q.pop();
      ++ans;
      for (int i = 0; i < dx.size(); ++i) {
        int x = node.first + dx[i], y = node.second + dy[i];
        if (x < 0 || y < 0 || x >= n || y >= n || grid[x][y] == '#' || vis[x][y]) continue;
        vis[x][y] = true;
        next.push({x, y});
      }
    }
    q = next;
  }
  // Output:
  cout << ans << endl;
  return 0;
}
