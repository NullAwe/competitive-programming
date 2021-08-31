#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  // Creates gray code with pattern:
  vector<vector<int>> code(1 << n, vector<int>(n));
  for (int i = 1; i <= n; ++i) {
    int ind = n - i;
    for (int j = 0; j < (1 << n); ++j) {
      int iter = j / (1 << (i - 1));
      if (iter > 0 && ((iter - 1) / 2) % 2 == 0) code[j][ind] = 1;
    }
  }
  // Output:
  for (vector<int> num : code) {
    for (int bit : num) cout << bit;
    cout << endl;
  }
  return 0;
}
