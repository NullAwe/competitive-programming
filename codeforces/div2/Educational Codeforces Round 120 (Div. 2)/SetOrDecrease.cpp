#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  ll k; cin >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  ll sum = 0; for (int num : arr) sum += num;
  ll need = sum - k;
  if (need <= 0) {
    cout << 0 << endl;
    return;
  }
  ll minOps = need;
  for (int i = n - 1; i > 0; --i) {
    need -= (arr[i] - arr[0]);
    if (need <= 0) {
      minOps = min(minOps, (ll) n - i);
      break;
    }
    ll val = n - i + (need / (n - i + 1));
    if (need % (n - i + 1) > 0) ++val;
    minOps = min(minOps, val);
  }
  // Output:
  cout << minOps << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
