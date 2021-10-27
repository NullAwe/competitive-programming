#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  // Output:
  if (n < 100) cout << "Easy" << endl;
  else if (n < 200) cout << "Medium" << endl;
  else cout << "Hard" << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}