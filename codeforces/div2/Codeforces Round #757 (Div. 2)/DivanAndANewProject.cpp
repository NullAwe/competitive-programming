#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<pair<int, int>> pairs(n); for (int i = 0; i < n; ++i) pairs[i] = {arr[i], i + 1};
  sort(pairs.begin(), pairs.end());
  ll sum = 0;
  int diff = 0;
  vector<int> ans(n + 1);
  for (int i = n - 1; i >= 0; --i) {
    if (i % 2 == (n - 1) % 2) ++diff;
    if (i % 2 == (n - 1) % 2) ans[pairs[i].second] = diff;
    else ans[pairs[i].second] = -diff;
    sum += (ll) 2 * diff * pairs[i].first;
  }
  // Output:
  cout << sum << endl;
  for (int num : ans) cout << num << ' ';
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
