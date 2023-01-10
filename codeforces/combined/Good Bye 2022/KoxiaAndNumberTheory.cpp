#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline void solve() {
  int n; cin >> n;
  vector<int> count(2);
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  set<ll> s; for (int i = 0; i < n; ++i) s.insert(arr[i]);
  if (s.size() != n) {
    cout << "NO\n";
    return;
  }
  for (int i = 2; i < 100; ++i) {
    vector<int> bkpts(i);
    for (ll num : arr) ++bkpts[num % i];
    bool all = true;
    for (int num : bkpts) if (num <= 1) all = false;
    if (all) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
