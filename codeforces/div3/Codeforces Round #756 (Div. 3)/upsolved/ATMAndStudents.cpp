#include <bits/stdc++.h>
using namespace std;

#define ll long long

void build(vector<pair<ll, pair<int, int>>>& t, int ind, int n) {
  if (ind >= n) return;
  build(t, ind * 2, n); build(t, ind * 2 + 1, n);
  int a = min(t[ind * 2].second.first, t[ind * 2 + 1].second.first),
        b = max(t[ind * 2].second.second, t[ind * 2 + 1].second.second);
  t[ind] = {0, {a, b}};
}

void modify(vector<pair<ll, pair<int, int>>>& t, int n, int p, ll value, vector<ll>& prefix) {
  for (t[p += n].first = value; p > 1; p >>= 1) {
    if ((p ^ 1) < p) p = p ^ 1;
    t[p >> 1].first = min(t[p].first, t[p ^ 1].first + prefix[t[p].second.second + 1] - prefix[t[p].second.first]);
  }
}

ll query(vector<pair<ll, pair<int, int>>>& t, int n, int l, int r, vector<ll>& prefix) {
  ll res = LLONG_MAX;
  int origLeft = l;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) {
      ll sum = prefix[t[l].second.first] - prefix[origLeft];
      res = min(res, sum + t[l++].first);
    }
    if (r & 1) {
      ll sum = prefix[t[r - 1].second.first] - prefix[origLeft];
      res = min(res, sum + t[--r].first);
    }
  }
  return res;
}

void solve() {
  int n; cin >> n;
  ll s; cin >> s;
  vector<pair<ll, pair<int, int>>> t(2 * n);
  for (int i = n; i < 2 * n; ++i) t[i] = {0, {i - n, i - n}};
  build(t, 1, n);
  // Creates prefix sums:
  vector<ll> prefix(n + 1);
  for (int i = 0; i < n; ++i) {
    ll a; cin >> a;
    prefix[i + 1] = prefix[i] + a;
  }
  // Builds the segment tree:
  for (int i = 0; i < n; ++i) modify(t, n, i, prefix[i + 1] - prefix[i], prefix);
  int ans = 0;
  int l = -1, r = -1;
  for (int i = 0; i < n; ++i) {
    // Runs binary search to find longest continuous subsequence starting at index i:
    int lo = i, hi = n + 1;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      ll res = query(t, n, i, mid, prefix);
      if (res == LLONG_MAX) break;
      if (s + res < 0) hi = mid;
      else lo = mid;
    }
    // Updates the answer:
    int range = lo - i;
    if (range > ans) {
      ans = range;
      l = i;
      r = lo;
    }
  }
  // Output:
  if (l >= 0) cout << l + 1 << ' ' << r << endl;
  else cout << -1 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
