#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const vector<int> dx = {0, 0, -1, 1}, dy = {-1, 1, 0, 0};

int main() {
  int n, m; cin >> n >> m;
  vector<string> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int rooms = 0;
  vector<vector<bool>> vis(n, vector<bool>(m));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (arr[i][j] == '#' || vis[i][j]) continue;
    ++rooms;
    queue<pii> q; q.push({i, j}); vis[i][j] = true;
    while (q.size()) {
      pii node = q.front(); q.pop();
      int x = node.first, y = node.second;
      for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m || arr[nx][ny] == '#' || vis[nx][ny]) continue;
        q.push({nx, ny}); vis[nx][ny] = true;
      }
    }
  }
  cout << rooms << '\n';
  return 0;
}
