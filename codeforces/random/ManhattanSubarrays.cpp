#include <bits/stdc++.h>
using namespace std;

bool row(int a, int b, int c) {
  return (a <= b && b <= c) || (a >= b && b >= c);
}

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int ans = 2 * n - 1;
  for (int i = 2; i < n; ++i) if (!row(arr[i - 2], arr[i - 1], arr[i])) ++ans;
  vector<vector<int>> checks(4);
  for (int i = 0; i < 4; ++i) {
    vector<int> add;
    for (int j = 0; j < 4; ++j) if (i != j) add.push_back(j);
    checks[i] = add;
  }
  for (int i = 3; i < n; ++i) {
    bool works = true;
    for (vector<int> check : checks) if (row(arr[i - check[0]], arr[i - check[1]], arr[i - check[2]])) works = false;
    if (works) ++ans;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
