#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline void solve() {
  int n; cin >> n;
  string s; cin >> s;
  int beg = 0, last = 0;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'B') {
      ans += i - max(beg, last);
      beg = beg + 1;
      last = i;
    }
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
