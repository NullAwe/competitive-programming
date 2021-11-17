#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll x, y; cin >> x >> y;
  // Output:
  if (x < y) {
    ll trygub = (x + y) / 2;
    trygub += (y % trygub - trygub % x);
    cout << trygub << endl;
  } else if (x == y) {
    cout << x << endl;
  } else {
    cout << x + y << endl;
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}