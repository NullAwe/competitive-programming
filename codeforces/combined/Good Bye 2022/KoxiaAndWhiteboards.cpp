#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline void solve() {
  int n, m; cin >> n >> m;
  multiset<int> arr; for (int i = 0; i < n; ++i) {int x; cin >> x; arr.insert(x);}
  for (int i = 0; i < m; ++i) {
    int x; cin >> x;
    arr.erase(arr.begin());
    arr.insert(x);
  }
  ll sum = 0;
  for (int num : arr) sum += num;
  cout << sum << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
