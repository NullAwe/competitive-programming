#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<pair<int, int>> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i].second >> arr[i].first;
  for (int i = 0; i < n; ++i) arr[i].second = 1000000001 - arr[i].second;
  map<pair<int, int>, int> m; for (int i = 0; i < n; ++i) m[arr[i]] = i;
  vector<pair<int, int>> ans(n);
  sort(arr.begin(), arr.end());
  int ml = INT_MAX;
  for (pair<int, int> p : arr) {
    ans[m[p]].first = ml <= p.second;
    ml = min(ml, p.second);
  }
  reverse(arr.begin(), arr.end());
  ml = 0;
  for (pair<int, int> p : arr) {
    ans[m[p]].second = ml >= p.second;
    ml = max(ml, p.second);
  }
  for (int i = 0; i < n; ++i) cout << ans[i].first << ' ';
  cout << '\n';
  for (int i = 0; i < n; ++i) cout << ans[i].second << ' ';
  cout << '\n';
  return 0;
}
