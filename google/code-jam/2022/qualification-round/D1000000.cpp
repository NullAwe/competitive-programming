#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
  int n; cin >> n;
  int arr[n]; for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr, arr + n);
  int ans = 0;
  for (int i = 0; i < n; ++i) if (arr[i] > ans) ++ans;
  cout << "Case #" << t << ": " << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) solve(i);
  return 0;
}
