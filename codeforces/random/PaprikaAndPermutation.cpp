#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  multiset<int> perm, arr; for (int i = 1; i <= n; ++i) perm.insert(i);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    if (perm.count(a)) perm.erase(a);
    else arr.insert(a);
  }
  int ans = perm.size();
  while (perm.size()) {
    if ((*perm.begin()) * 2 >= (*arr.begin())) {
      cout << -1 << '\n';
      return;
    }
    perm.erase(perm.begin());
    arr.erase(arr.begin());
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
