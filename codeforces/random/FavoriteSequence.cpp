#include <iostream>
using namespace std;

void solve() {
  int n; cin >> n;
  int arr[n], ans[n], ind = -1; for (int i = 0; i < n; ++i) cin >> arr[i];
  if (n % 2) ans[++ind] = arr[n / 2];
  for (int i = n / 2 - 1; i >= 0; --i) ans[++ind] = arr[n - i - 1], ans[++ind] = arr[i];
  for (int i = n - 1; i >= 0; --i) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
