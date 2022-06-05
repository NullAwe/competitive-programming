#include <bits/stdc++.h>
using namespace std;

#define ll long long

int t;
vector<int> m;

bool can(ll check) {
  ll p = 0;
  for (int num : m) {
    p += check / num;
    if (p >= t) return true;
  }
  return false;
}

int main() {
  int n; cin >> n >> t;
  m = vector<int>(n); for (int i = 0; i < n; ++i) cin >> m[i];
  ll lo = 0, hi = 1e18;
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    if (can(mid)) hi = mid;
    else lo = mid;
  }
  cout << hi << '\n';
  return 0;
}
