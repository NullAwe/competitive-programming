#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string str, ans; cin >> str; ans += str[0];
  for (int i = 1; i < n; ++i) {
    if (str[i] > str[i - 1] || (str[i] == str[i - 1] && str[i] == str[0])) break;
    ans += str[i];
  }
  string copy = ans; reverse(copy.begin(), copy.end());
  // Output:
  cout << ans << copy << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
