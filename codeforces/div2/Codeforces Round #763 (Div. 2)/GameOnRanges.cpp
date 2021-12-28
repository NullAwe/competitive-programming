#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<pair<int, int>> ranges(n);
  for (int i = 0; i < n; ++i) cin >> ranges[i].first >> ranges[i].second;
  sort(ranges.begin(), ranges.end());
  set<pair<int, int>> has;
  int ind = 0;
  for (int i = 1; i <= n; ++i) {
    while (ind < n && ranges[ind].first <= i) {
      has.insert({ranges[ind].second, ranges[ind].first});
      ++ind;
    }
    pair<int, int> val = *has.begin(); has.erase(has.begin());
    // Output:
    cout << val.second << ' ' << val.first << ' ' << i << endl;
  }
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
