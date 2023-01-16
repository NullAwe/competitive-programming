#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  int others = n - 1, ans = 1;
  for (int i = n - 1; i >= 0; --i) {
    int beg = i;
    while (i >= 0 && (arr[i] > others || (arr[i] == beg && arr[i] == others)))
      --i, --others;
    if (i == n - 1) {
      --others;
      continue;
    }
    if (arr[i + 1] > others + 1) ++ans;
    --others;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
