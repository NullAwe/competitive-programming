#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  vector<pair<int, int>> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i].second >> arr[i].first;
  sort(arr.begin(), arr.end());
  multiset<int> e;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (!e.size() || e.upper_bound(arr[i].second) == e.begin()) {
      if (e.size() < k) ++ans, e.insert(arr[i].first);
      continue;
    }
    ++ans;
    e.erase(--e.upper_bound(arr[i].second));
    e.insert(arr[i].first);
  }
  cout << ans << '\n';
  return 0;
}

