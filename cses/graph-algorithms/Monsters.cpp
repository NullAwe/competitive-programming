#include <bits/stdc++.h>
using namespace std;
 
const vector<int> dx = {0, 0, -1, 1}, dy = {-1, 1, 0, 0};
const vector<char> dirs = {'R', 'L', 'D', 'U'};
 
int main() {
  int n, m;
  cin >> n >> m;
  vector<string> lab(n);
  for (int i = 0; i < n; ++i) cin >> lab[i];
  vector<vector<int>> monsters(n, vector<int>(m, 0)), me(n, vector<int>(m, 0));
  pair<int, int> yo;
  vector<pair<int, int>> mons;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (lab[i][j] == '#') {
        monsters[i][j] = -1;
        me[i][j] = -1;
      } else if (lab[i][j] == 'A') {
        monsters[i][j] = -2;
        yo = {i, j};
      } else if (lab[i][j] == 'M') {
        me[i][j] = -2;
        mons.push_back({i, j});
      } else {
        monsters[i][j] = -2;
        me[i][j] = -2;
      }
    }
  }
  queue<pair<int, int>> p, q;
  for (pair<int, int> mon : mons) p.push(mon);
  while (p.size()) {
    pair<int, int> cur = p.front();
    p.pop();
    for (int i = 0; i < 4; ++i) {
      int x = cur.first + dx[i], y = cur.second + dy[i];
      if (x < 0 || y < 0 || x >= n || y >= m || monsters[x][y] > -2) continue;
      monsters[x][y] = monsters[cur.first][cur.second] + 1;
      p.push({x, y});
    }
  }
  q.push(yo);
  while (q.size()) {
    pair<int, int> cur = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int x = cur.first + dx[i], y = cur.second + dy[i];
      if (x < 0 || y < 0 || x >= n || y >= m || me[x][y] > -2) continue;
      me[x][y] = me[cur.first][cur.second] + 1;
      q.push({x, y});
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (monsters[i][j] < -1) monsters[i][j] = 2000000;
      if (me[i][j] < -1) me[i][j] = 2000000;
    }
  }
  pair<int, int> goal;
  goal = {-1, -1};
  for (int i = 0; i < m; ++i) {
    if (lab[0][i] != '#' && me[0][i] < monsters[0][i]) {
      goal = {0, i};
      break;
    } else if (lab[n - 1][i] != '#' && me[n - 1][i] < monsters[n - 1][i]) {
      goal = {n - 1, i};
      break;
    }
  }
  for (int i = 0; i < n; ++i) {
    if (lab[i][0] != '#' && me[i][0] < monsters[i][0]) {
      goal = {i, 0};
      break;
    } else if (lab[i][m - 1] != '#' && me[i][m - 1] < monsters[i][m - 1]) {
      goal = {i, m - 1};
      break;
    }
  }
  if (goal.first < 0 && goal.second < 0) {
    cout << "NO";
    return 0;
  }
  cout << "YES\n" << me[goal.first][goal.second] << "\n";
  vector<char> path(me[goal.first][goal.second]);
  for (int i = path.size() - 1; i >= 0; --i) {
    for (int j = 0; j < 4; ++j) {
      int x = goal.first + dx[j], y = goal.second + dy[j];
      if (x < 0 || y < 0 || x >= n || y >= m) continue;
      if (me[x][y] == i) {
        path[i] = dirs[j];
        goal = {x, y};
        break;
      }
    }
  }
  for (char ch : path) cout << ch;
  cout << '\n';
  return 0;
}
