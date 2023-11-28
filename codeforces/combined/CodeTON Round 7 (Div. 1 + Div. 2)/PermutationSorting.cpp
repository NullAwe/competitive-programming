#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

struct SumSegtree {

  int n;
  vector<ll> t;

  SumSegtree(int n) : n(n), t(2 * n) {}

  void upd(int p, int v) {
    for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }

  ll qry(int l, int r) {
    ll ans = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans += t[l++];
      if (r & 1) ans += t[--r];
    }
    return ans;
  }
};

inline void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) --arr[i];
  vector<pii> intervals;
  vector<vector<int>> begins(2 * n);
  for (int i = 0; i < n; ++i) {
    if (arr[i] < i) intervals.push_back({arr[i] + n, i}), begins[arr[i] + n].push_back(i);
    else intervals.push_back({arr[i], i}), begins[arr[i]].push_back(i), begins[arr[i] + n].push_back(i + n);
  }
  vector<int> ans(n);
  sort(intervals.begin(), intervals.end());
  SumSegtree st(2 * n);
  int id = 0;
  for (int i = 0; i < 2 * n; ++i) {
    for (int b : begins[i]) st.upd(b, 1);
    while (id < intervals.size() && intervals[id].first == i) {
      int l = intervals[id].second, r = intervals[id].first;
      ans[r % n] = r - l - st.qry(l + 1, r);
      ++id;
    }
  }
  for (int i = 0; i < n; ++i) cout << ans[i] << " ";
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
