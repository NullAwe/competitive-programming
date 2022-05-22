#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string str; cin >> str;
  int num = 0;
  for (int i = n / 2 - 1; i >= 0; --i) {
    if (str[i] == str[i + 1]) ++num;
    else break;
  }
  cout << num * 2 + n % 2 << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
