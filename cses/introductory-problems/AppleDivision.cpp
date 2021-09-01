#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll ans = INT_MAX;
  // Tries every possible way to make two sets:
  for (int i = 0; i < (1 << n); ++i) {
    ll sum = 0;
    for (int j = 0; j < n; ++j)
      sum += (((i >> j) & 1) * 2 - 1) * arr[j];
    ans = min(ans, abs(sum));
  }
  // Output:
  cout << ans << endl;
  return 0;
}
