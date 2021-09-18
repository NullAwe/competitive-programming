#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n; cin >> n;
    string str; cin >> str;
    int changes = 0;
    char cur = ' ';
    for (int j = 0; j < n; ++j) {
      char ch = str[j];
      if (ch == 'O' || ch == 'X') {
        if (cur == ' ') cur = ch;
        if (ch != cur) {
          // Increments changes because he has to switch hands:
          cur = ch;
          ++changes;
        }
      }
    }
    cout << "Case #" << i << ": " << changes << endl;
  }
  return 0;
}
