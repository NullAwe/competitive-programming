#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n, l, r, k; cin >> n >> l >> r >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> ac; for (int num : arr) if (l <= num && num <= r) ac.push_back(num);
  sort(ac.begin(), ac.end());
  ll sum = 0;
  int ans = 0;
  for (int num : ac) {
    if (sum + num > k) break;
    ++ans;
    sum += num;
  }
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
