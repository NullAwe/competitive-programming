#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  vector<pair<int, int>> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i].first;
  for (int i = 0; i < n; ++i) arr[i].second = i + 1;
  sort(arr.begin(), arr.end());
  for (int i = 0; i < n; ++i) {
    int target = k - arr[i].first;
    for (int j = i + 1; j < n - 1; ++j) {
      if (arr[j].first + arr[j].first == target) {
        if (arr[j + 1].first == arr[j].first) {
          cout << arr[i].second << ' ' << arr[j].second << ' ' << arr[j + 1].second << '\n';
          return 0;
        }
      } else if (target - arr[j].first > arr[j].first) {
        auto it = lower_bound(arr.begin(), arr.end(), pair<int, int>({target - arr[j].first, 0}));
        if (it == arr.end() || (*it).first != target - arr[j].first) continue;
        cout << arr[i].second << ' ' << arr[j].second << ' ' << (*it).second << '\n';
        return 0;
      }
    }
  }
  cout << "IMPOSSIBLE\n";
  return 0;
}
