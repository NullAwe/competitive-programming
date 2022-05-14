#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll n; cin >> n;
  cout << (n % 2 || n == 2 ? "-1" : to_string(n / 6 + (n % 6 > 0)) + " " + to_string(n / 4)) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
