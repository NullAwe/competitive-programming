#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, a, b; cin >> n >> a >> b;
  // Output:
  if (abs(a - b) > 1 || a + b > n - 2) {
    cout << -1 << endl;
    return;
  }
  if (a >= b) {
    for (int i = 0; i < n - a - b - 1; ++i) cout << i + 1 << ' ';
    for (int i = n - a - b - 1; i < n; i += 2) {
      int val = (i / 2 + 1) * 2 + i % 2;
      if (i == n - 1) cout << n << ' ';
      else cout << val << ' ' << val - 1 << ' ';
    }
  } else {
    for (int i = 0; i < n - a - b - 1; ++i) cout << n - i << ' ';
    for (int i = n - a - b - 1; i < n; i += 2) {
      int val = (i / 2 + 1) * 2 + i % 2;
      if (i == n - 1) cout << 1 << ' ';
      else cout << n + 1 - val << ' ' << n + 2 - val << ' ';
    }
  }
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
