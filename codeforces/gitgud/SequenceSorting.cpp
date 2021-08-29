#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> sorted = arr;
  sort(sorted.begin(), sorted.end());
  vector<pair<int, int>> ends(n + 1, {-1, -1});
  for (int i = 0; i < n; ++i) {
    if (ends[arr[i]].first < 0) ends[arr[i]].first = i;
    ends[arr[i]].second = i;
  }
  // Finds largest cardinality of a complete subset of the sorted array
  // that appears as a subsequence in the original array:
  int count = 0, ml = 1, length = 0;
  pair<int, int> last = {-1, -1};
  for (int i = 0; i <= n; ++i) {
    if (ends[i].first < 0) continue;
    ++count;
    if (ends[i].first > last.second) ++length;
    else {
      ml = max(ml, length);
      length = 1;
    }
    last = ends[i];
  }
  ml = max(ml, length);
  // Output:
  cout << count - ml << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
