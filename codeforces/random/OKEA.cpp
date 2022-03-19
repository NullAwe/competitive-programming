#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  if (k == 1) {
    cout << "YES\n";
    for (int i = 1; i <= n; ++i) cout << i << '\n';
    return;
  }
  if (n % 2) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  for (int i = 0; i < n / 2; ++i) {
    for (int j = 0; j < k; ++j) cout << (i * k + j) * 2 + 1 << ' ';
    cout << '\n';
  }
  for (int i = n / 2; i < n; ++i) {
    for (int j = 0; j < k; ++j) cout << ((i - n / 2) * k + j) * 2 + 2 << ' ';
    cout << '\n';
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
