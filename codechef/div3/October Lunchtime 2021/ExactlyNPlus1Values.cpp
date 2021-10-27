#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  // Output:
  cout << "1 1";
  if (n == 1) {
    // Output:
    cout << endl;
    return;
  }
  ll sum = 1; for (int i = 0; i < n; ++i) sum *= 2;
  sum -= 2;
  for (int i = 2; i <= n - 1; ++i) {
    // Output:
    cout << ' ' << i;
    sum -= i;
  }
  // Output:
  cout << ' ' << sum << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}