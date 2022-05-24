#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  set<int> use; for (int i = 1; i <= n; ++i) use.insert(i);
  vector<int> perm(n); perm[0] = arr[0]; use.erase(arr[0]);
  for (int i = 1; i < n; ++i) {
    if (use.count(arr[i])) perm[i] = arr[i], use.erase(arr[i]);
    else {
      auto it = use.upper_bound(arr[i]);
      if (it == use.begin()) {
        cout << "-1\n";
        return;
      }
      --it;
      perm[i] = *it, use.erase(it);
    }
  }
  for (int num : perm) cout << num << ' ';
  cout << '\n';
}  

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
