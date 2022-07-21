#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int ind, ans = 1; cin >> ind;
  vector<int> arr(3); for (int i = 0; i < 3; ++i) cin >> arr[i];
  while (arr[ind - 1]) {
    int tmp = arr[ind - 1];
    ++ans, arr[ind - 1] = 0, ind = tmp;
  }
  cout << (ans == 3 ? "YES\n" : "NO\n");
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
