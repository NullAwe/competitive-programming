#include <bits/stdc++.h>
using namespace std;
 
const vector<int> dx = {0, 0, -1, 1}, dy = {-1, 1, 0, 0};
const vector<char> dirs = {'R', 'L', 'D', 'U'};
 
int main() {
  int n, m;
  cin >> n >> m;
  vector<string> lab(n);
  for (int i = 0; i < n; ++i) cin >> lab[i];
  vector<vector<int>> ranks(n, vector<int>(m, 0));
  pair<int, int> a, b;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (lab[i][j] == '#') ranks[i][j] = -1;
      else if (lab[i][j] == 'A') a = {i, j};
      else if (lab[i][j] == 'B') b = {i, j};
    }
  }
  queue<pair<int, int>> q;
  q.push(a);
  while (q.size()) {
    pair<int, int> cur = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int x = cur.first + dx[i], y = cur.second + dy[i];
      if (x < 0 || y < 0 || x >= n || y >= m || x == a.first && y == a.second || ranks[x][y] != 0) continue;
      ranks[x][y] = ranks[cur.first][cur.second] + 1;
      q.push({x, y});
    }
  }
  if (ranks[b.first][b.second] == 0) {
    cout << "NO";
    return 0;
  }
  cout << "YES\n";
  cout << ranks[b.first][b.second] << "\n";
  pair<int, int> cur = b;
  vector<char> path(ranks[b.first][b.second]);
  for (int i = ranks[b.first][b.second] - 1; i >= 0; --i) {
    for (int j = 0; j < 4; ++j) {
      int x = cur.first + dx[j], y = cur.second + dy[j];
      if (x < 0 || y < 0 || x >= n || y >= m) continue;
      if (ranks[x][y] == i) {
        path[i] = dirs[j];
        cur = {x, y};
        break;
      }
    }
  }
  for (char ch : path) cout << ch;
  return 0;
}
