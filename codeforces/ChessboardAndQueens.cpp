#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll getNum(vector<string> board, int x, int y, int queens) {
  if (queens == 0) return 1;
  if (x > 7) return 0;
  bool can = board[x][y] == '.';
  // Checks if placement is valid:
  for (int i = 0; i < 8; ++i)
    if (board[x][i] == 'Q' || board[i][y] == 'Q' ||
      (x + i < 8 && y + i < 8 && board[x + i][y + i] == 'Q') ||
      (x - i >= 0 && y - i >= 0 && board[x - i][y - i] == 'Q') ||
      (x + i < 8 && y - i >= 0 && board[x + i][y - i] == 'Q') ||
      (x - i >= 0 && y + i < 8 && board[x - i][y + i] == 'Q')) can = false;
  int nx = x, ny = 0;
  if (y == 7) nx = x + 1;
  else ny = y + 1;
  ll ans = getNum(board, nx, ny, queens);
  if (!can) return ans;
  board[x][y] = 'Q';
  return ans + getNum(board, nx, ny, queens - 1);
}

int main() {
  vector<string> board(8);
  for (int i = 0; i < 8; ++i) cin >> board[i];
  // Output:
  cout << getNum(board, 0, 0, 8) << endl;
  return 0;
}

