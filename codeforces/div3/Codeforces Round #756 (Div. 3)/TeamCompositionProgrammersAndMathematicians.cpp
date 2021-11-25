#include <bits/stdc++.h>
using namespace std;

void solve() {
  int a, b; cin >> a >> b;
  // Output (min takes care of if there isn't enough people of one type):
  cout << min((a + b) / 4, min(a, b)) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
