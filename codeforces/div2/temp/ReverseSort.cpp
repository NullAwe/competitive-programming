#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string str; cin >> str;
  int ones = 0;
  for (int i = 0; i < n; ++i) if (str[i] == '1') ++ones;
  bool one = false, can = true;
  for (int i = 0; i < n; ++i) {
    if (str[i] == '1') one = true;
    else if (one) can = false;
  }
  if (can) {
    // Output:
    cout << 0 << endl;
    return;
  }
  vector<int> ans;
  for (int i = 0; i < n - ones; ++i)
    if (str[i] == '1') ans.push_back(i + 1);
  for (int i = n - ones; i < n; ++i)
    if (str[i] == '0') ans.push_back(i + 1);
  // Output:
  cout << 1 << endl << ans.size();
  for (int num : ans) cout << ' ' << num;
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
