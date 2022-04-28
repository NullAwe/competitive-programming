#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
  int n, m; cin >> n >> m;
  cout << "Case #" << t << ":\n";
  for (int i = 0; i < n * 2 + 1; ++i) {
    for (int j = 0; j < m * 2 + 1; ++j) {
      if ((i < 2 && j < 2) || ((i & 1) == 1 && (j & 1) == 1)) cout << '.';
      else if ((i & 1) == 0 && (j & 1) == 0) cout << '+';
      else if ((i & 1) == 0) cout << '-';
      else cout << '|';
    }
    cout << '\n';
  }
}

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) solve(i);
  return 0;
}
