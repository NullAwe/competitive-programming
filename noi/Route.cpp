#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>

#define _sq(x) (x) * (x)

ll a, b, c;

inline bool chgd(const pll& x, const pll& y, int t) {
  int td1 = t - x.second, td2 = t - y.second;
  if (td1 < 0 || td2 < 0) return false;
  return x.first + a * _sq(td1) + b * td1 >= y.first + a * _sq(td2) + b * td2;
}

inline int chgt(const pll& x, const pll& y) {
  int lo = max(x.second, y.second) - 1, hi = 1001;
  while (lo < hi - 1) {
    int mid = (lo + hi) >> 1;
    if (chgd(x, y, mid)) hi = mid;
    else lo = mid;
  }
  return hi;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m >> a >> b >> c;
  vector<vector<int>> chg(1002);
  vector<int> nodes(m + 1);
  vector<set<pair<int, pll>>> dqs(n);
  dqs[0].insert({0, {0, 0}});
  vector<pair<pii, pii>> ts(m);
  vector<vector<pair<pii, pii>>> trs(1001);
  for (int i = 0; i < m; ++i) {
    int s, t, b, e; cin >> s >> t >> b >> e; --s, --t;
    ts[i] = {{e, b}, {s, t}};
  }
  sort(ts.begin(), ts.end());
  for (int i = 0; i < m; ++i) {
    trs[ts[i].first.second].push_back({ts[i].second, {ts[i].first.first, i + 1}});
    nodes[i + 1] = ts[i].second.second;
  }
  ll mn = LLONG_MAX;
  for (int t = 0; t <= 1000; ++t) {
    for (int num : chg[t]) {
      int idx = nodes[num];
      while (dqs[idx].size()) {
        auto it = dqs[idx].lower_bound({num, {0, 0}});
        if (it == dqs[idx].begin() || it->first != num) break;
        if (chgd(prev(it)->second, it->second, t)) dqs[idx].erase(prev(it));
        else break;
      }
      while (dqs[idx].size()) {
        auto it = dqs[idx].lower_bound({num, {0, 0}});
        if (it == --dqs[idx].end() || it->first != num) break;
        if (chgd(it->second, next(it)->second, t)) dqs[idx].erase(it);
        else break;
      }
      if (!dqs[idx].size()) continue;
      auto it = dqs[idx].lower_bound({num, {0, 0}});
      if (it->first != num) continue;
      int val = 1001;
      if (it != dqs[idx].begin()) val = chgt(prev(it)->second, it->second);
      if (it != --dqs[idx].end()) val = min(val, chgt(it->second, next(it)->second));
      chg[val].push_back(num);
    }
    for (pair<pii, pii> tr : trs[t]) {
      if (!dqs[tr.first.first].size()) continue;
      pll x = dqs[tr.first.first].begin()->second;
      int td = t - x.second;
      if (td < 0) continue;
      ll cost = x.first + a * _sq(td) + b * td + c;
      dqs[tr.first.second].insert({tr.second.second, {cost, tr.second.first}});
      auto it = dqs[tr.first.second].lower_bound({tr.second.second, {0, 0}});
      int val = 1001;
      if (it != dqs[tr.first.second].begin()) val = chgt(prev(it)->second, it->second);
      if (it != --dqs[tr.first.second].end()) val = min(val, chgt(it->second, next(it)->second));
      chg[val].push_back(tr.second.second);
      if (tr.first.second == n - 1) mn = min(mn, cost + tr.second.first);
    }
  }
  cout << mn << '\n';
  return 0;
}
