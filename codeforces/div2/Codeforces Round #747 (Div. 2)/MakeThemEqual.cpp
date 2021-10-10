#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  char c; cin >> c;
  string str; cin >> str;
  bool bef = false, aft = str[n - 1] != c;
  for (int i = 0; i < n - 1; ++i) {
    if (str[i] != c) {
      bef = true;
      break;
    }
  }
  vector<int> ans;
  if (bef) ans.push_back(n);
  if (aft) ans.push_back(n - 1);
  if (ans.size() < 2) {
    // Output:
    cout << ans.size() << endl;
    if (ans.size()) cout << ans[0] << endl;
    return;
  }
  vector<int> div(n + 1);
  for (int i = 1; i <= n; ++i) {
    if (str[i - 1] == c) continue;
    for (int j = 1; j * j <= n; ++j) {
      if (i % j == 0) {
        ++div[j];
        ++div[i / j];
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (div[i] == 0) {
      // Output:
      cout << "1\n" << i << endl;
      return;
    }
  }
  // Output:
  cout << ans.size() << endl;
  for (int num : ans) cout << num << ' ';
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
