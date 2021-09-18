#include <bits/stdc++.h>
using namespace std;

void solve() {
  string bin; cin >> bin;
  int groups = 0, cur = -1;
  for (int i = 0; i < bin.size(); ++i) {
    if (cur != bin[i] - '0') {
      cur = bin[i] - '0';
      if (cur == 0) ++groups;
    }
  }
  // Output:
  cout << min(groups, 2) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}