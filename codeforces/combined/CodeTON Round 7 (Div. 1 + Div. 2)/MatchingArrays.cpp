#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

inline void solve() {
  int n, x; cin >> n >> x;
  vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
  vector<int> copy = a;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  vector<int> newa(n);
  for (int i = 0; i < n; ++i) newa[i] = a[(i + n - x) % n];
  int count = 0;
  for (int i = 0; i < n; ++i) if (newa[i] > b[i]) ++count;
  if (count != x) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  multiset<pii> s;
  for (int i = 0; i < n; ++i) s.insert({newa[i], b[i]});
  for (int i = 0; i < n; ++i) {
    auto it = *s.lower_bound({copy[i], 0});
    cout << it.second << ' ';
    s.erase(s.find(it));
  }
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
