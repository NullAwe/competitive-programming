#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<vector<int>> avail(n, vector<int>(5, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 5; ++j) {
      cin >> avail[i][j];
    }
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = i + 1; j < 5; ++j) {
      bool canDo = true;
      int l = 0, r = 0;
      for (int k = 0; k < n; ++k) {
        if (avail[k][i] == 0 && avail[k][j] == 0) {
          canDo = false;
          break;
        }
        if (avail[k][i] == 1) ++l;
        if (avail[k][j] == 1) ++r;
      }
      if (canDo && l >= n / 2 && r >= n / 2) {
        // Output:
        cout << "YES" << endl;
        return;
      }
    }
  }
  // Output:
  cout << "NO" << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
