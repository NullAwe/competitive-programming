#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n; cin >> n;
    vector<string> board(n);
    for (int j = 0; j < n; ++j) cin >> board[j];
    vector<vector<int>> go;
    int m = INT_MAX;
    // Checks all rows:
    for (int j = 0; j < n; ++j) {
      bool hasO = false;
      vector<int> moves;
      for (int k = 0; k < n; ++k) {
        if (board[j][k] == 'O') {
          hasO = true;
          break;
        } else if (board[j][k] == '.') moves.push_back(j * n + k);
      }
      sort(moves.begin(), moves.end());
      if (hasO) continue;
      for (vector<int> went : go) {
        if (went == moves) {
          hasO = true;
          break;
        }
      }
      if (moves.size() < m) {
        m = moves.size();
        go.resize(0);
        go.push_back(moves);
      } else if (moves.size() == m && !hasO) go.push_back(moves);
    }
    // Checks all columns:
    for (int j = 0; j < n; ++j) {
      bool hasO = false;
      vector<int> moves;
      for (int k = 0; k < n; ++k) {
        if (board[k][j] == 'O') {
          hasO = true;
          break;
        } else if (board[k][j] == '.') moves.push_back(k * n + j);
      }
      sort(moves.begin(), moves.end());
      if (hasO) continue;
      for (vector<int> went : go) {
        if (went == moves) {
          hasO = true;
          break;
        }
      }
      if (moves.size() < m) {
        m = moves.size();
        go.resize(0);
        go.push_back(moves);
      } else if (moves.size() == m && !hasO) go.push_back(moves);
    }
    // Output:
    string ans = (m == INT_MAX ? "Impossible" : to_string(m) + " " + to_string(go.size()));
    cout << "Case #" << i << ": " << ans << endl;
  }
  return 0;
}
