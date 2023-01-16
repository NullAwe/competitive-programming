#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

inline void solve() {
  int n; cin >> n;
  vector<pair<pii, pii>> arr(n);
  map<pair<pii, pii>, int> mp;
  for (int i = 0; i < n; ++i) {
    int u, l, d, r; cin >> u >> l >> d >> r;
    arr[i] = {{r, u}, {d - u + 1, r - l + 1}};
    mp[arr[i]] = i;
  }
  sort(arr.begin(), arr.end());
  set<pii> sold1, sold2;
  set<pair<pii, pair<bool, int>>> indiv1, indiv2;
  for (auto _p : arr) {
    int ind = mp[_p];
    int end = _p.first.first;
    int row = _p.first.second;
    int h = _p.second.first;
    int w = _p.second.second;
    int beg = end - w + 1;
    if (h == 2) {
      while (sold1.upper_bound({beg, 0}) != sold1.end()) sold1.erase(sold1.upper_bound({beg, 0}));
      while (indiv1.lower_bound({{beg, 0}, {0, 0}}) != indiv1.end())
        indiv1.erase(indiv1.lower_bound({{beg, 0}, {0, 0}}));
      if (sold1.size()) {
        pii p = *--sold1.end();
        if (p.second >= beg - 1) {
          sold1.erase(p);
          p.second = end;
          sold1.insert(p);
        } else {
          sold1.insert({beg, end});
        }
      } else {
        sold1.insert({beg, end});
      }
      if (indiv1.size()) {
        auto p = *--indiv1.end();
        if (p.first.second >= beg - 1) {
          indiv1.erase(p);
          p.first.second = beg - 1;
          indiv1.insert(p);
        }
      }
      indiv1.insert({{beg, end}, {1, ind}});
      while (sold2.upper_bound({beg, 0}) != sold2.end()) {
        auto it = sold2.upper_bound({beg, 0});
        sold2.erase(it);
      }
      while (indiv2.lower_bound({{beg, 0}, {0, 0}}) != indiv2.end()) {
        auto it = indiv2.lower_bound({{beg, 0}, {0, 0}});
        indiv2.erase(it);
      }
      if (sold2.size()) {
        pii p = *--sold2.end();
        if (p.second >= beg - 1) {
          sold2.erase(p);
          p.second = end;
          sold2.insert(p);
        } else {
          sold2.insert({beg, end});
        }
      } else {
        sold2.insert({beg, end});
      }
      if (indiv2.size()) {
        auto p = *--indiv2.end();
        if (p.first.second >= beg - 1) {
          indiv2.erase(p);
          p.first.second = beg - 1;
          indiv2.insert(p);
        }
      }
      indiv2.insert({{beg, end}, {1, ind}});
    } else if (row == 1) {
      auto _it = sold1.upper_bound({beg + 1, 0});
      if (_it != sold1.begin()) {
        --_it;
        pii p = *_it;
        if (p.second >= beg) {
          beg = p.second + 1, w = end - beg + 1;
        }
      }
      if (!w) continue;
      while (sold1.upper_bound({beg, 0}) != sold1.end()) {
        auto it = sold1.upper_bound({beg, 0});
        sold1.erase(it);
      }
      while (indiv1.lower_bound({{beg, 0}, {0, 0}}) != indiv1.end()) {
        auto it = indiv1.lower_bound({{beg, 0}, {0, 0}});
        indiv1.erase(it);
      }
      if (sold1.size()) {
        pii p = *--sold1.end();
        if (p.second >= beg - 1) {
          sold1.erase(p);
          p.second = end;
          sold1.insert(p);
        } else {
          sold1.insert({beg, end});
        }
      } else {
        sold1.insert({beg, end});
      }
      if (indiv1.size()) {
        auto p = *--indiv1.end();
        if (p.first.second >= beg - 1) {
          indiv1.erase(p);
          p.first.second = beg - 1;
          indiv1.insert(p);
        }
      }
      indiv1.insert({{beg, end}, {0, ind}});
    } else {
      auto _it = sold2.upper_bound({beg + 1, 0});
      if (_it != sold2.begin()) {
        --_it;
        pii p = *_it;
        if (p.second >= beg) {
          beg = p.second + 1, w = end - beg + 1;
        }
      }
      if (!w) continue;
      while (sold2.upper_bound({beg, 0}) != sold2.end()) {
        auto it = sold2.upper_bound({beg, 0});
        sold2.erase(it);
      }
      while (indiv2.lower_bound({{beg, 0}, {0, 0}}) != indiv2.end()) {
        auto it = indiv2.lower_bound({{beg, 0}, {0, 0}});
        indiv2.erase(it);
      }
      if (sold2.size()) {
        pii p = *--sold2.end();
        if (p.second >= beg - 1) {
          sold2.erase(p);
          p.second = end;
          sold2.insert(p);
        } else {
          sold2.insert({beg, end});
        }
      } else {
        sold2.insert({beg, end});
      }
      if (indiv2.size()) {
        auto p = *--indiv2.end();
        if (p.first.second >= beg - 1) {
          indiv2.erase(p);
          p.first.second = beg - 1;
          indiv2.insert(p);
        }
      }
      indiv2.insert({{beg, end}, {0, ind}});
    }
  }
  ll ans = 0;
  for (pii p : sold1) ans += p.second - p.first + 1;
  for (pii p : sold2) ans += p.second - p.first + 1;
  cout << ans << endl;
  vector<pair<pii, pii>> ar(n);
  for (auto p : indiv1) ar[p.second.second] = {{1, p.first.first}, {1, p.first.second}};
  for (auto p : indiv2) {
    if (!p.second.first || ar[p.second.second].first.first == 0)
      ar[p.second.second] = {{2, p.first.first}, {2, p.first.second}};
    else ar[p.second.second].second.first = 2;
  }
  for (auto p : ar)
    cout << p.first.first << ' ' << p.first.second << ' ' << p.second.first << ' ' << p.second.second << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
