#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n, k; cin >> n >> k;
  int top = n, bot = 1, count = 1;
  while (top >= bot) {
    if (count % k == 0) cout << bot++ << ' ';
    else cout << top-- << ' ';
    ++count;
  }
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
