#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll a, b, c; cin >> a >> b >> c;
  // Output:
  cout << ((a + 2 * b + 3 * c) % 2) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}