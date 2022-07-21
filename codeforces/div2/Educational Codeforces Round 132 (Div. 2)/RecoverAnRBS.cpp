#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  string str; cin >> str;
  int n = str.size(), q = 0, b = 0;
  for (int i = 0; i < n; ++i) q += str[i] == '?', b += (str[i] == '(' ? 1 : (str[i] == ')' ? -1 : 0));
  int l = (q - b) / 2, r = (q + b) / 2;
  if (!l || !r) {
    cout << "YES\n";
    return;
  }
  b = 0; vector<int> bs(n);
  for (int i = 0; i < n; ++i) {
    if (str[i] == '?') {
      if (l) ++b, --l;
      else --b;
    } else b += (str[i] == '(' ? 1 : -1);
    bs[i] = b;
  }
  int count = 0, m = INT_MAX;
  for (int i = n - 1; i >= 0; --i) {
    if (count == r) m = min(m, bs[i]);
    count += str[i] == '?';
  }
  cout << (m >= 2 ? "NO\n" : "YES\n");
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
