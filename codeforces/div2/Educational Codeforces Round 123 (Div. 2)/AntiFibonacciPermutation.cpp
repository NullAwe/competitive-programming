#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  if (n == 3) {
    cout << "3 2 1\n1 3 2\n3 1 2\n";
    return;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i; j > 0; --j) cout << j << ' ';
    for (int j = n; j > i; --j) cout << j << ' ';
    cout << '\n';
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
