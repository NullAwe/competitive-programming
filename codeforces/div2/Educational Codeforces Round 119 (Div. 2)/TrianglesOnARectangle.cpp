#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll w, h, ans = 0; cin >> w >> h;
  for (int i = 0; i < 4; ++i) {
    int k; cin >> k;
    ll first = 0, last = 0;
    for (int j = 0; j < k; ++j) {
      int a; cin >> a;
      if (first == 0) first = a;
      last = a;
    }
    ans = max(ans, (i < 2 ? h : w) * (last - first));
  }
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
