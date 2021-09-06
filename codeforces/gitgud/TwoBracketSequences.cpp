#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 201;

int memo[MAX_N][MAX_N][MAX_N];

int main() {
  string s, t; cin >> s >> t;
  for (int i = 0; i < MAX_N; ++i) memo[s.size()][t.size()][i] = i;
  // Finds answer using dynamic programming:
  for (int i = s.size(); i >= 0; --i) {
    for (int j = t.size(); j >= 0; --j) {
      for (int k = MAX_N - 1; k >= 0; --k) {
        if (i == s.size() && j == t.size()) continue;
        memo[i][j][k] = INT_MAX;
        if (k < MAX_N - 1) {
          int ii = i, jj = j;
          if (i < s.size() && s[i] == '(') ++ii;
          if (j < t.size() && t[j] == '(') ++jj;
          if (memo[ii][jj][k + 1] < INT_MAX) memo[i][j][k] = memo[ii][jj][k + 1] + 1;
        }
        if (k > 0) {
          int ii = i, jj = j;
          if (i < s.size() && s[i] == ')') ++ii;
          if (j < t.size() && t[j] == ')') ++jj;
          if (ii == i && jj == j) continue;
          if (memo[ii][jj][k - 1] < INT_MAX) memo[i][j][k] = min(memo[i][j][k], memo[ii][jj][k - 1] + 1);
        }
      }
    }
  }
  // Constructs sequence from dynamic programming results:
  int curI = 0, curJ = 0, curK = 0;
  while (memo[curI][curJ][curK] > 0) {
    if (curK < MAX_N - 1) {
      int ii = curI, jj = curJ;
      if (curI < s.size() && s[curI] == '(') ++ii;
      if (curJ < t.size() && t[curJ] == '(') ++jj;
      if (memo[ii][jj][curK + 1] == memo[curI][curJ][curK] - 1) {
        // Output:
        cout << '(';
        curI = ii;
        curJ = jj;
        ++curK;
        continue;
      }
    }
    if (curK > 0) {
      int ii = curI, jj = curJ;
      if (curI < s.size() && s[curI] == ')') ++ii;
      if (curJ < t.size() && t[curJ] == ')') ++jj;
      if (memo[ii][jj][curK - 1] == memo[curI][curJ][curK] - 1) {
        // Output:
        cout << ')';
        curI = ii;
        curJ = jj;
        --curK;
        continue;
      }
    }
  }
  // Final output:
  cout << endl;
  return 0;
}
