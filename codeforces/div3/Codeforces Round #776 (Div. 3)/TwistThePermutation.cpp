#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> ans(n);
  for (int i = n; i > 0; --i) {
    int index = 0;
    for (int j = 0; j < n; ++j) {
      if (arr[j] == i) {
        index = j;
        break;
      }
    }
    ans[i - 1] = (index + 1) % i;
    vector<int> rotated(n);
    for (int j = 0; j < n; ++j) rotated[j] = arr[(j + (index + 1) % i) % i];
    arr = rotated;
  }
  for (int num : ans) cout << num << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
