#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  string str; cin >> str;
  string rev = str; reverse(rev.begin(), rev.end());
  if (k == 0 || str == rev) cout << "1\n";
  else cout << "2\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
