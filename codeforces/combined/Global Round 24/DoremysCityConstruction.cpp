#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  if (arr[0] == arr[n - 1]) {
    cout << n / 2 << '\n';
    return;
  }
  ll mp = 0;
  for (int i = 0; i < n; ++i) {
    if (i == 0 || arr[i] == arr[i - 1]) continue;
    mp = max(mp, (ll) i * (n - i));
  }
  cout << mp << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
