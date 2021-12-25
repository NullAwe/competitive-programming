#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    sum += a;
  }
  // Output:
  cout << (sum % n == 0 ? 0 : 1) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
