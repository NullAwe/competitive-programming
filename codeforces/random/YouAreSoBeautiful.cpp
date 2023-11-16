#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<bool> first(n);
  set<int> s;
  for (int i = 0; i < n; ++i) {
    if (!s.count(arr[i])) {
      first[i] = true;
      s.insert(arr[i]);
    }
  }
  vector<bool> last(n);
  int total = 0;
  s.clear();
  for (int i = n - 1; i >= 0; --i) {
    if (!s.count(arr[i])) {
      last[i] = true;
      s.insert(arr[i]);
      ++total;
    }
  }
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    if (first[i]) ans += total;
    if (last[i]) --total;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}