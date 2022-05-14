#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n, q; cin >> n >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll sum = 0; for (int num : arr) sum += num;
  int last = -1;
  set<int> changes;
  for (int i = 0; i < q; ++i) {
    int t; cin >> t;
    if (t == 1) {
      int p, a; cin >> p >> a; --p;
      sum += a - (last < 0 || changes.count(p) ? arr[p] : last);
      if (last >= 0 && !changes.count(p)) changes.insert(p);
      arr[p] = a;
    } else {
      int a; cin >> a;
      last = a, sum = (ll) a * n, changes.clear();
    }
    cout << sum << '\n';
  }
}

int main() {
  solve();
  return 0;
}
