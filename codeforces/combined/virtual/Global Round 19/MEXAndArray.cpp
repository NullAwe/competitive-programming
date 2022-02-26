#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int zero = 0;
    for (int j = i; j < n; ++j) {
      if (arr[j] == 0) ++zero;
      ans += j - i + 1 + zero;
    }
  }
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

