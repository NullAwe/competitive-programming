#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> map(n + 1); for (int i = 0; i < n; ++i) map[arr[i]] = i;
  set<pair<int, int>> existing;
  vector<int> changes(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    int num = arr[i];
    auto it = existing.upper_bound({num, i});
    if (it != existing.end()) {
      pair<int, int> u = *it;
      if (it == existing.begin()) ++changes[arr[i]];
      else {
        --it;
        pair<int, int> b = *it;
        if (u.second > b.second) ++changes[arr[i]];
      }
    }
    if (arr[i] > 1) if (map[arr[i] - 1] > map[arr[i]]) --changes[arr[i]];
    existing.insert({num, i});
  }
  // Output:
  int sum = 0;
  for (int i = 0; i <= n; ++i) {
    sum += changes[i];
    cout << sum << endl;
  }
  return 0;
}
