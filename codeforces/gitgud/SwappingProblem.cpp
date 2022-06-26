#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

int main() {
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  vector<pii> l, r;
  for (int i = 0; i < n; ++i) {
    if (a[i] < b[i]) l.push_back({a[i], b[i]});
    else if (a[i] > b[i]) r.push_back({b[i], a[i]});
  }
  sort(l.begin(), l.end());
  sort(r.begin(), r.end());
  set<pii> ls, rs; ls.insert({0, 0}), rs.insert({0, 0});
  set<int> h;
  int mr = 0;
  for (int i = 0; i < l.size(); ++i) {
    mr = max(mr, l[i].second);
    if (h.count(l[i].first)) ls.erase(ls.upper_bound({l[i].first, 0}));
    ls.insert({l[i].first, mr}), h.insert(l[i].first);
  }
  h.clear();
  mr = 0;
  for (int i = 0; i < r.size(); ++i) {
    mr = max(mr, r[i].second);
    if (h.count(r[i].first)) rs.erase(rs.upper_bound({r[i].first, 0}));
    rs.insert({r[i].first, mr}), h.insert(r[i].first);
  }
  mr = 0;
  for (int i = 0; i < l.size(); ++i) {
    int e = min((*--rs.upper_bound({l[i].first, INT_MAX})).second, l[i].second);
    mr = max(mr, 2 * (e - l[i].first));
  }
  for (int i = 0; i < r.size(); ++i) {
    int e = min((*--ls.upper_bound({r[i].first, INT_MAX})).second, r[i].second);
    mr = max(mr, 2 * (e - r[i].first));
  }
  ll ans = -mr;
  for (int i = 0; i < n; ++i) ans += abs(a[i] - b[i]);
  cout << ans << '\n';
  return 0;
}

