#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};
vector<char> ms = {'^', 'v', '<', '>'};

pii qry(int x, int y, vector<string> arr) {
  cout << "? " << x << ' ' << y << endl;
  for (string str : arr) cout << str << endl;
  cin >> x >> y;
  return {x, y};
}

int main() {
  int n; cin >> n;
  for (int x = 0; x < n; x += n - 1) for (int y = 0; y < n; y += n - 1) for (int sd = 0; sd < 4; ++sd) {
    int d = sd;
    int nx = x + dx[d], ny = y + dy[d];
    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
    vector<string> board(n, string(n, ' '));
    int done = 0;
    nx = x, ny = y;
    for (int done = 0; done < n * n - 1; ++done) {
      int nnx = nx + dx[d],  nny = ny + dy[d];
      if (nnx < 0 || nnx >= n || nny < 0 || nny >= n) {
        for (int td = 0; td < 4; ++td) {
          nnx = nx + dx[td], nny = ny + dy[td];
          if (nnx < 0 || nnx >= n || nny < 0 || nny >= n) continue;
          if (board[nnx][nny] != ' ') continue;
          board[nx][ny] = ms[td];
          nx = nnx, ny = nny, d ^= 1;
          break;
        }
      } else {
        board[nx][ny] = ms[d];
        nx = nnx, ny = nny;
      }
    }
    board[nx][ny] = ms[d];
    pii end = {nx + dx[d] + 1, ny + dy[d] + 1};
    pii ans = qry(x + 1, y + 1, board);
    if (ans == end) continue;
    if (ans.first >= 0) {
      if (ans.first == 0) cout << "! 1 " << ans.second << " ^" << endl;
      else if (ans.second == 0) cout << "! " << ans.first << " 1 <" << endl;
      else if (ans.first == n + 1) cout << "! " << n << " " << ans.second << " v" << endl;
      else cout << "! " << ans.first << " " << n << " >" << endl;
      return 0;
    }
    int lo = 0, hi = n * n;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      int px = x, py = y;
      for (int i = 0; i < mid; ++i) {
        int idx = find(ms.begin(), ms.end(), board[px][py]) - ms.begin();
        px += dx[idx], py += dy[idx];
      }
      if (qry(px + 1, py + 1, board).first < 0) lo = mid;
      else hi = mid;
    }
    int px = x, py = y;
    for (int i = 0; i < lo; ++i) {
      int idx = find(ms.begin(), ms.end(), board[px][py]) - ms.begin();
      px += dx[idx], py += dy[idx];
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
      if (i == px && j == py) continue;
      if (i < px) board[i][j] = '^';
      else if (i > px) board[i][j] = 'v';
      else if (j < py) board[i][j] = '<';
      else board[i][j] = '>';
    }
    char forbid = board[px][py];
    for (int i = 0; i < 4; ++i) {
      if (ms[i] == forbid) continue;
      nx = px + dx[i], ny = py + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
      board[px][py] = ms[i], board[nx][ny] = ms[i ^ 1];
      if (qry(px + 1, py + 1, board).first < 0) {
        cout << "! " << px + 1 << " " << py + 1 << " " << board[px][py] << endl;
        return 0;
      }
    }
  }
  return 0;
}
