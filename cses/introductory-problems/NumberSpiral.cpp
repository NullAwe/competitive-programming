#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll x, y; cin >> x >> y;
  ll width = x < y ? y : x;
  pair<ll, ll> end;
  if (width % 2 == 0) end = {width, 1};
  else end = {1, width};
  ll dist = abs(x - end.first) + abs(y - end.second);
  // Output:
  cout << width * width - dist << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
