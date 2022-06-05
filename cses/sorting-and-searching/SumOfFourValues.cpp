#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  vector<pair<int, int>> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i].first;
  for (int i = 0; i < n; ++i) arr[i].second = i + 1;
  sort(arr.begin(), arr.end());
  map<int, pair<int, int>> ml, mr;
  set<int> s;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int sum = arr[i].first + arr[j].first;
      pair<int, int> pl = ml[sum], pr = mr[sum];
      if (pl.second == 0 || pl.second > j) ml[sum] = {i, j};
      if (pr.second == 0 || pr.first < i) mr[sum] = {i, j};
      s.insert(sum);
    }
  }
  for (int sum : s) {
    pair<int, int> pl = ml[sum], pr = mr[k - sum];
    if (pl.second < pr.first) {
      cout << arr[pl.first].second << ' ' << arr[pl.second].second << ' ' << arr[pr.first].second << ' ' << arr[pr.second].second << '\n';
      return 0;
    }
  }
  cout << "IMPOSSIBLE\n";
  return 0;
}
