#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Stores indices of each parity:
  vector<vector<int>> p(2);
  for (int i = 0; i < n; ++i) p[arr[i] % 2].push_back(i);
  int diff = p[0].size() - p[1].size();
  if (abs(diff) > 1) {
    cout << -1 << endl;
    return;
  }
  if (n % 2 == 1) {
    int start = (p[0].size() > p[1].size() ? 0 : 1), ind = 0;
    ll ans = 0;
    for (int i = 0; i < n; i += 2) {
      ans += abs(p[start][ind] - i);
      ++ind;
    }
    // Output:
    cout << ans << endl;
  } else {
    int ind = 0;
    ll ans = 0;
    for (int i = 0; i < n; i += 2) {
      ans += abs(p[0][ind] - i);
      ++ind;
    }
    ind = 0;
    ll comp = 0;
    for (int i = 0; i < n; i += 2) {
      comp += abs(p[1][ind] - i);
      ++ind;
    }
    // Output:
    cout << min(ans, comp) << endl;
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
