#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll n, s; cin >> n >> s;
  cout << s / (n * n) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
