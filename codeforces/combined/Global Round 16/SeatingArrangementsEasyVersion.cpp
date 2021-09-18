#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<int> arr(m); for (int i = 0; i < m; ++i) cin >> arr[i];
  vector<int> sorted = arr;
  sort(sorted.begin(), sorted.end());
  int ans = 0;
  vector<bool> taken(m, false);
  for (int i = 0; i < arr.size(); ++i) {
    int ind = -1;
    ans += i;
    for (int j = arr.size() - 1; j >= 0; --j) {
      if (taken[j]) {
        --ans;
        continue;
      }
      if (arr[i] == sorted[j]) {
        ind = j;
        break;
      }
    }
    taken[ind] = true;
  }
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}