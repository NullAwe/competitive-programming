#include <bits/stdc++.h>
using namespace std;

void solve() {
  string str; cin >> str;
  char ch; cin >> ch;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == ch && i % 2 == 0) {
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
