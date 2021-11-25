#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string str = to_string(n);
  // Output:
  if ((str[str.size() - 1] - '0') % 2 == 0) cout << 0 << endl;
  else if ((str[0] - '0') % 2 == 0) cout << 1 << endl;
  else {
    for (int i = 1; i < str.size(); ++i) {
      if ((str[i] - '0') % 2 == 0) {
        // Output:
        cout << 2 << endl;
        return;
      }
    }
    // Output:
    cout << -1 << endl;
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
