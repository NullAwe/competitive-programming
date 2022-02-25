#include <bits/stdc++.h>
using namespace std;

void solve() {
  string s, t; cin >> s >> t;
  sort(s.begin(), s.end());
  map<char, int> m; m['a'] = 0, m['b'] = 1, m['c'] = 2;
  int abc[3]; abc[0] = abc[1] = abc[2] = 0;
  for (int i = 0; i < s.size(); ++i) if (m.count(s[i])) ++abc[m[s[i]]];
  for (int i = 0; i < abc[0]; ++i) cout << 'a';
  if (t == "abc" && abc[0]) {
    for (int i = 0; i < abc[2]; ++i) cout << 'c';
    for (int i = 0; i < abc[1]; ++i) cout << 'b';
  } else {
    for (int i = 0; i < abc[1]; ++i) cout << 'b';
    for (int i = 0; i < abc[2]; ++i) cout << 'c';
  }
  cout << s.substr(abc[0] + abc[1] + abc[2], s.size() - abc[0] - abc[1] - abc[2]);
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
