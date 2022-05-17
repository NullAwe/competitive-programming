#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int has = INT_MAX, must = 0;
  for (int i = 0; i < n; ++i) {
    arr[i] -= must;
    if (arr[i] < 0) {
      cout << "NO\n";
      return;
    }
    has = min(has, arr[i]);
    must = max(must, must + arr[i] - has);
  }
  cout << "YES\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
