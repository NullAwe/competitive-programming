#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n, at = 4; cin >> n;
  if (n == 1) {
    cout << "1\n";
    return;
  } else if (n == 2) {
    cout << "1 2\n";
    return;
  }
  vector<int> ans(n);
  ans[0] = 3, ans[(n - 1) / 2] = 1, ans[n - 1] = 2;
  for (int i = 1; ans[i] == 0; ++i) ans[i] = at++;
  for (int i = (n - 1) / 2 + 1; ans[i] == 0; ++i) ans[i] = at++;
  for (int num : ans) cout << num << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
