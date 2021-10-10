#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> topic(n), diff(n);
  for (int i = 0; i < n; ++i) cin >> topic[i] >> diff[i];
  map<int, int> t, d;
  for (int num : topic) ++t[num];
  for (int num : diff) ++d[num];
  ll m = 0;
  for (int i = 0; i < n; ++i) m += (ll) (t[topic[i]] - 1) * (d[diff[i]] - 1);
  // Output:
  cout << (ll) n * (n - 1) * (n - 2) / 6 - m << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
