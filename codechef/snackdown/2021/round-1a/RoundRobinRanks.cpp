#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll n, k; cin >> n >> k;
  ll maxWins = n * (n - 1) / 2 - (n - k) * (n - k - 1) / 2;
  // Output:
  cout << min(maxWins / k, n - 1) * 2 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
