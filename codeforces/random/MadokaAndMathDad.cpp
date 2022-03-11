#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  int sum = 0, val = (n % 3 == 0 || n % 3 == 2) ? 2 : 1;
  while (sum != n) {
    cout << val;
    sum += val;
    val = 3 - val;
  }
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
