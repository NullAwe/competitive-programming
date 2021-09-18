#include <bits/stdc++.h>
using namespace std;

#define ll long long


void solve() {
  int n, s; cin >> n >> s;
  int lo = 0, hi = s + 1;
  // Binary searches for the answer:
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    ll sum = (ll) mid * (n / 2 + 1);
    if (s - sum < 0) hi = mid;
    else lo = mid;
  }
  // Output:
  cout << lo << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}