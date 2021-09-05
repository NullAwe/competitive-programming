#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string str; cin >> str;
  for (int i = 0; i < n; ++i) {
    // Output:
    if (str[i] == 'U') cout << 'D';
    else if (str[i] == 'D') cout << 'U';
    else cout << str[i];
  }
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}