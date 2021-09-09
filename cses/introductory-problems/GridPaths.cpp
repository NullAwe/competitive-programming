#include <bits/stdc++.h>
using namespace std;

bool grid[7][7];
int input[48];
int ans = 0, ind = 0;
 
bool avail(int x, int y) {
  return x >= 0 && x < 7 && y >= 0 && y < 7 && !grid[x][y];
}

void paths(int x, int y) {
  if (ind >= 48 && x == 6 && y == 0) {
	  ++ans;
	  return;
  }
  if (ind >= 48 || (x == 6 && y == 0) || !avail(x, y)) return;
  // Stops if the grid has split the grid into two, which we cannot fill:
  bool a = avail(x, y - 1), b = avail(x, y + 1), c = avail(x - 1, y), d = avail(x + 1, y);
  if ((a && b && !c && !d) || (!a && !b && c && d)) return;
  grid[x][y] = true;
  int num = input[ind];
  ++ind;
  if (num == -1) {
	  // Tries all directions:
	  paths(x, y - 1);
	  paths(x, y + 1);
	  paths(x + 1, y);
	  paths(x - 1, y);
  }
  // Moves in a specific direction:
  else if (num == 0) paths(x + 1, y);
  else if (num == 1) paths(x - 1, y);
  else if (num == 2) paths(x, y - 1);
  else paths(x, y + 1);
  grid[x][y] = false;
  --ind;
}
 
int main() {
  // Enables fast IO for optimization:
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string str; cin >> str;
  for (int i = 0; i < 48; ++i) {
  	if (str[i] == '?') input[i] = -1;
  	else if (str[i] == 'D') input[i] = 0;
  	else if (str[i] == 'U') input[i] = 1;
	  else if (str[i] == 'L') input[i] = 2;
  	else input[i] = 3;
  }
  // Finds all paths following the input starting at (0, 0):
  paths(0, 0);
  // Output:
  cout << ans << endl;
  return 0;
}
