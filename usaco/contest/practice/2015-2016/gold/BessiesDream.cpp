#include <bits/stdc++.h>
using namespace std;

const vector<int> DX = {1, -1, 0, 0}, DY = {0, 0, -1, 1};

// Stores the current position of Bessie:
struct State {

  int x, y, dir, orange;
  
  State(int a, int b, int c, int d) {
    x = a;
    y = b;
    dir = c;
    orange = d;
  }
};

int main() {
  ifstream in("dream.in");
  ofstream out("dream.out");
  int n, m; in >> n >> m;
  int grid[n][m], d[n][m][4][2];
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) in >> grid[i][j];
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < 4; ++k) for (int l = 0; l < 2; ++l) d[i][j][k][l] = -1;
  queue<State> q;
  for (int i = 0; i < 4; ++i) {
    d[0][0][i][0] = 0;
    q.push(State(0, 0, i, 0));
  }
  // Finds answer using BFS:
  while (q.size()) {
    for (int sz = q.size(); sz > 0; --sz) {
      State now = q.front(); q.pop();
      vector<State> adj;
      int x = now.x, y = now.y, dir = now.dir, orange = now.orange;
      if (grid[x][y] == 2) orange = true;
      else if (grid[x][y] == 4) orange = false;
      bool forwards = true;
      if (grid[x][y] == 4) {
        int nx = x + DX[dir], ny = y + DY[dir];
	    if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == 0 || grid[nx][ny] == 3) forwards = false;
	    else adj.push_back(State(nx, ny, dir, orange));
      }
      if ((grid[x][y] == 4) ^ forwards) {
        for (int i = 0; i < DX.size(); ++i) {
          int nx = x + DX[i], ny = y + DY[i];
          if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == 0 || (grid[nx][ny] == 3 && !orange)) continue;
          adj.push_back(State(nx, ny, i, orange));
        }
      }
      for (State next : adj) {
        int& cell = d[next.x][next.y][next.dir][next.orange];
        if (cell < 0) {
          q.push(next);
          cell = INT_MAX;
        }
        cell = min(cell, d[now.x][now.y][now.dir][now.orange] + 1);
      }
    }
  }
  int ans = INT_MAX;
  for (int i = 0; i < 4; ++i) {
    if (d[n - 1][m - 1][i][0] >= 0) ans = min(ans, d[n - 1][m - 1][i][0]);
    if (d[n - 1][m - 1][i][1] >= 0) ans = min(ans, d[n - 1][m - 1][i][1]);
  }
  // Output:
  out << (ans == INT_MAX ? -1 : ans) << endl;
  return 0;
}
