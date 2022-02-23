#include <bits/stdc++.h>
using namespace std;

void solve() {
  string str; cin >> str;
  vector<bool> rgb(3);
  map<char, int> m; m['r'] = m['R'] = 0, m['g'] = m['G'] = 1, m['b'] = m['B'] = 2;
  for (char ch : str) {
    if (ch >= 97) rgb[m[ch]] = true;
    else if (!rgb[m[ch]]) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
