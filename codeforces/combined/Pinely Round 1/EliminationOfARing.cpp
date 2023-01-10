#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  if (n % 2) {
    cout << n << '\n';
    return;
  }
  bool alt = true;
  for (int i = 2; i < n; ++i) if (arr[i] != arr[i - 2]) alt = false;
  cout << (alt ? n / 2 + 1 : n) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
