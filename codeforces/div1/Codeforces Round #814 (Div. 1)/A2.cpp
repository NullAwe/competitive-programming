#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  set<int> xors; xors.insert(0);
  int cur = 0, ans = 0;
  for (int i = 0; i < n; ++i) {
    if (xors.count(arr[i] ^ cur)) {
      xors.clear(), xors.insert(0), cur = 0;
      continue;
    }
    cur ^= arr[i];
    xors.insert(arr[i] ^ cur), xors.insert(cur);
    ++ans;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
