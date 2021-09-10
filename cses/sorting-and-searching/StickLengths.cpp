#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  ll ans = 0;
  for (int i = 0; i < n; ++i) ans += abs(arr[i] - arr[n / 2]);
  // Output:
  cout << ans << endl;
  return 0;
}
