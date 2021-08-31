#include <bits/stdc++.h>
using namespace std;

int getPos(int a, int b) {
  if (a != 1 && b != 1) return 1;
  if (a != 2 && b != 2) return 2;
  return 3;
}

void fill(int n, int from, int to, vector<pair<int, int>>& moves) {
  if (n < 1) return;
  if (n == 1) {
    moves.push_back({from, to});
    return;
  }
  int pos = getPos(from, to);
  if (n % 2 == 1) pos = to;
  for (int i = 1; i <= n; ++i) {
    // Starts the stack of height i:
    moves.push_back({from, pos});
    int newPos = getPos(from, pos);
    // Fills the stack of height i:
    fill(i - 1, newPos, pos, moves);
    pos = newPos;
  }
}

int main() {
  int n; cin >> n;
  vector<pair<int, int>> moves;
  fill(n, 1, 3, moves);
  // Output:
  cout << moves.size() << endl;
  for (pair<int, int> m : moves) cout << m.first << " " << m.second << endl;
  return 0;
}
