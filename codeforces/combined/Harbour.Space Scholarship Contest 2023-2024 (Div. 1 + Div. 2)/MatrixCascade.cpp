#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n, ans = 0; cin >> n;
  vector<string> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<bool>> mnall(n, vector<bool>(n)), mnleft(n, vector<bool>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      bool flipped = mnall[i][j] ^ mnleft[i][j];
      if (flipped ^ (arr[i][j] == '1')) mnall[i][j] = !mnall[i][j], ++ans;
      if (i < n - 1) {
        if (mnleft[i][j] && j > 0) mnleft[i + 1][j - 1] = !mnleft[i + 1][j - 1];
        if (mnall[i][j]) {
          if (j > 0) mnleft[i + 1][j - 1] = !mnleft[i + 1][j - 1];
          if (j < n - 1) mnleft[i + 1][j] = !mnleft[i + 1][j], mnall[i + 1][j + 1] = !mnall[i + 1][j + 1];
          else mnall[i + 1][j] = !mnall[i + 1][j];
        }
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
