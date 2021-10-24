#include <bits/stdc++.h>
using namespace std;

int t(string& str, char ignore) {
  int rem = 0;
  for (char ch : str) if (ch == ignore) ++rem;
  int l = 0, r = str.size() - 1;
  while (l <= r) {
    if (str[l] == ignore && str[r] == ignore) {
      if (l != r) --rem;
      --rem; ++l; --r;
    } else if (str[l] == ignore) ++l;
    else if (str[r] == ignore) --r;
    else if (str[l] != str[r]) return INT_MAX;
    else { ++l; --r; }
  }
  return rem;
}

void solve() {
  int n; cin >> n;
  string str; cin >> str;
  int ans = INT_MAX;
  for (int i = 0; i < 26; ++i) ans = min(ans, t(str, (char) (i + 'a')));
  // Output:
  cout << (ans == INT_MAX ? -1 : ans)  << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}