#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll ans = 0;
  for (int i = 1; i < n; ++i) {
    ans += max(arr[i - 1] - arr[i], 0);
    arr[i] = max(arr[i], arr[i - 1]);
  }
  // Output:
  cout << ans << endl;
  return 0;
}
