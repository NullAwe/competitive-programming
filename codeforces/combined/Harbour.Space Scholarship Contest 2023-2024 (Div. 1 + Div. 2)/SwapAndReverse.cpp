#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  string s; cin >> s;
  if (k % 2 == 0) {
    sort(s.begin(), s.end());
    cout << s << '\n';
  } else {
    string first = "", second = "";
    for (int i = 0; i < n; ++i) {
      if (i & 1) second += s[i];
      else first += s[i];
    }
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());
    for (int i = 0; i < n; ++i) {
      if (i & 1) cout << second[i / 2];
      else cout << first[i / 2];
    }
    cout << '\n';
  }
}

int main() {
    int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
