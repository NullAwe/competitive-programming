#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> copy = arr;
  sort(copy.begin(), copy.end());
  if (arr[0] == copy[0]) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
