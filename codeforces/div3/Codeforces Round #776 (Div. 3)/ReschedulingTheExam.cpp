#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int _min = arr[0] - 1, ind = 0;
  for (int i = 1; i < n; ++i) {
    if (arr[i] - arr[i - 1] - 1 < _min) {
      _min = arr[i] - arr[i - 1] - 1;
      ind = i;
    }
  }
  vector<int> todo; todo.push_back(ind);
  if (ind) todo.push_back(ind - 1);
  int ans = 0;
  for (int index : todo) {
    vector<int> copy = arr;
    copy[index] = INT_MAX; sort(copy.begin(), copy.end());
    int last = 0, maxFix = -1, val = 0;
    for (int i = 0; i < n - 1; ++i) {
      int middle = (last + copy[i]) / 2;
      if (middle - last - 1 > maxFix && copy[i] - middle - 1 > maxFix) {
        val = middle;
        maxFix = min(middle - last - 1, copy[i] - middle - 1);
      }
      last = copy[i];
    }
    if (k - copy[n - 2] - 1 > maxFix) val = k;
    copy[n - 1] = val;
    sort(copy.begin(), copy.end());
    int comp = copy[0] - 1;
    for (int i = 1; i < n; ++i) comp = min(comp, copy[i] - copy[i - 1] - 1);
    ans = max(ans, comp);
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
