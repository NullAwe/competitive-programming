#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll n, v; cin >> n >> v;
  // Output:
  cout << n * (n - 1) / 2 << ' ';
  if (v > n - 2) {
    // Output:
    cout << n - 1 << endl;
    return;
  }
  ll cost = v - 1;
  n -= v;
  // Output:
  cout << cost + n * (n + 1) / 2 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}