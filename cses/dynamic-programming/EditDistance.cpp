#include <bits/stdc++.h>
using namespace std;
 
int main() {
  string s, t;
  cin >> s >> t;
  vector<vector<int>> memo(s.size() + 1, vector<int>(t.size() + 1));
  for (int i = 0; i <= s.size(); ++i) memo[i][0] = i;
  for (int j = 0; j <= t.size(); ++j) memo[0][j] = j;
  for (int i = 1; i <= s.size(); ++i) {
    for (int j = 1; j <= t.size(); ++j) {
      if (s[i - 1] == t[j - 1]) memo[i][j] = memo[i - 1][j - 1];
      else memo[i][j] = min(min(memo[i - 1][j], memo[i][j - 1]), memo[i - 1][j - 1]) + 1;
    }
  }
  cout << memo[s.size()][t.size()] << "\n";
  return 0;
}
