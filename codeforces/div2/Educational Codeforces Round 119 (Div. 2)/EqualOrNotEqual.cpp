#include <bits/stdc++.h>
using namespace std;

void solve() {
  string str; cin >> str;
  int n = 0;
  for (int i = 0; i < str.size(); ++i) if (str[i] == 'N') ++n;
  // Output:
  cout << (n == 1 ? "NO" : "YES") << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
