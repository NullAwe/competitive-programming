#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n; cin >> n;
    string str; cin >> str;
    ll minus = 0, changes = 0, lastEnd = -1, llEnd = -1, ans = 0;
    char cur = ' ';
    for (int j = 0; j < n; ++j) {
      char ch = str[j];
      minus += changes;
      if (ch == 'O' || ch == 'X') {
        if (cur == ' ') cur = ch;
        if (cur != ch) {
          cur = ch;
          ++changes;
          minus += j - llEnd - 1;
        }
        llEnd = j;
      }
      ans = (ans + ((j * changes) % MOD) - minus + MOD) % MOD;
      minus %= MOD;
    }
    // Output:
    cout << "Case #" << i << ": " << ans << endl;
  }
  return 0;
}
