#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<string> grid(2);
  for (int i = 0; i < 2; ++i) cin >> grid[i];
  for (int i = 0; i < n; ++i) {
    if (grid[0][i] == '1' && grid[1][i] == '1') {
      // Output:
      cout << "NO" << endl;
      return;
    }
  }
  // Output:
  cout << "YES" << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
