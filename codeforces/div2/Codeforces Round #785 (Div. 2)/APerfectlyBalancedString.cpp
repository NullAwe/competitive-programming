#include <bits/stdc++.h>
using namespace std;

void solve() {
  string str; cin >> str;
  vector<bool> present(26); for (int i = 0; i < str.size(); ++i) present[str[i] - 'a'] = true;
  for (int i = 0; i < 26; ++i) {
    if (!present[i]) continue;
    vector<bool> last(26);
    bool begun = false;
    for (int j = 0; j < str.size(); ++j) {
      if (!begun && str[j] - 'a' != i) continue;
      if (str[j] - 'a' == i) {
        if (!begun) begun = true;
        else {
          for (int k = 0; k < 26; ++k) {
            if (present[k] && !last[k]) {
              cout << "NO\n";
              return;
            }
          }
        }
        last = vector<bool>(26);
      }
      last[str[j] - 'a'] = true;
    }
  }
  cout << "YES\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
