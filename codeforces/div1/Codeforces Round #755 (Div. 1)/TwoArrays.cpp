#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i] && a[i] + 1 != b[i]) {
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
