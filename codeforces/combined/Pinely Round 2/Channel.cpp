#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n, a, q; cin >> n >> a >> q;
  string s; cin >> s;
  if (n == a) {
    cout << "YES\n";
    return;
  }
  int mn = a;
  for (int i = 0; i < q; ++i) {
    if (s[i] == '+') ++mn;
    else --mn;
    if (mn == n) {
      cout << "YES\n";
      return;
    }
  }
  int cp = 0;
  for (int i = 0; i < q; ++i) cp += s[i] == '+';
  if (cp + a >= n) {
    cout << "MAYBE\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
