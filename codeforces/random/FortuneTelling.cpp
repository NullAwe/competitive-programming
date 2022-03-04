#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll n, x, y; cin >> n >> x >> y;
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    x ^= a;
  }
  cout << (x % 2 == y % 2 ? "Alice\n" : "Bob\n");
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
