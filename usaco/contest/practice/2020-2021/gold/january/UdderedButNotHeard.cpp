#include <bits/stdc++.h>
using namespace std;

int main() {
  string line; cin >> line;
  vector<int> shrink(26, -1);
  int code = 0;
  for (char ch : line) if (shrink[ch - 'a'] < 0) shrink[ch - 'a'] = code++;
  vector<vector<int>> map(code, vector<int>(code));
  for (int i = 1; i < line.size(); ++i) map[shrink[line[i] - 'a']][shrink[line[i - 1] - 'a']]++;
  vector<int> memo(1 << code, INT_MAX);
  memo[0] = 0;
  for (int i = 1; i < (1 << code); ++i) {
    for (int j = 0; j < code; ++j) {
      if ((i & (1 << j)) == 0) continue;
      int last = i ^ (1 << j), add = memo[last];
      for (int k = 0; k < code; ++k) if ((last & (1 << k)) == 0) add += map[j][k];
      memo[i] = min(memo[i], add);
    }
  }
  // Output:
  cout << memo[(1 << code) - 1] + 1 << endl;
  return 0;
}
