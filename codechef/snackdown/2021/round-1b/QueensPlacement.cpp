#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  // Output:
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j && (i == 1 || i > 2)) cout << 'Q';
      else cout << '.';
    }
    cout << endl;
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
