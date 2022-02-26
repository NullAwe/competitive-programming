#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> copy = arr; sort(copy.begin(), copy.end());
  for (int i = 0; i < n; ++i) {
    if (arr[i] != copy[i]) {
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

