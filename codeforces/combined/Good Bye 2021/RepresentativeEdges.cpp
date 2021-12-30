#include <bits/stdc++.h>
using namespace std;

const int MAX_X = 201;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int mh = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < n; ++j) {
      vector<int> diffs; map<int, int> m;
      for (int k = i + j; k < n; k += j) {
        int steps = (k - i) / j;
        int diff = arr[k] - arr[i];
        if (diff % steps) continue;
        if (!m[diff / steps]) diffs.push_back(diff / steps);
        ++m[diff / steps];
      }
      int thm = 0; for (int diff : diffs) thm = max(thm, m[diff]);
      mh = max(mh, thm + 1);
    }
  }
  // Output:
  cout << n - mh << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
