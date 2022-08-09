#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MAX_GCD = 1e5;

vector<ll> tmax, tsum, lazy;

inline void push(int v, int tl, int tr) {
  if (!lazy[v]) return;
  tmax[2 * v] = tmax[2 * v + 1] = lazy[v];
  int m = (tl + tr) / 2, rl = m - tl + 1, rr = tr - m;
  tsum[2 * v] = rl * lazy[v], tsum[2 * v + 1] = rr * lazy[v];
  lazy[2 * v] = lazy[2 * v + 1] = lazy[v], lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int val) {
  if (l > r) return;
  if (tl == l && tr == r) lazy[v] = val, tmax[v] = lazy[v], tsum[v] = (tr - tl + 1) * lazy[v];
  else {
    push(v, tl, tr);
    int m = (tl + tr) / 2;
    update(2 * v, tl, m, l, min(m, r), val), update(2 * v + 1, m + 1, tr, max(m + 1, l), r, val);
    tmax[v] = max(tmax[2 * v], tmax[2 * v + 1]);
    tsum[v] = tsum[2 * v] + tsum[2 * v + 1];
  }
}

ll qmax(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (tl == l && tr == r) return tmax[v];
  push(v, tl, tr);
  int m = (tl + tr) / 2;
  return max(qmax(2 * v, tl, m, l, min(m, r)), qmax(2 * v + 1, m + 1, tr, max(m + 1, l), r));
}

ll qsum(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (tl == l && tr == r) return tsum[v];
  push(v, tl, tr);
  int m = (tl + tr) / 2;
  return qsum(2 * v, tl, m, l, min(m, r)) + qsum(2 * v + 1, m + 1, tr, max(m + 1, l), r);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<pair<int, int>> firsts(MAX_GCD + 1, {-1, -1}), lasts(MAX_GCD + 1, {-1, -1});
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j * j <= arr[i]; ++j) {
      if (arr[i] % j) continue;
      if (firsts[j].first < 0) firsts[j].first = i;
      else if (firsts[j].second < 0) firsts[j].second = i;
      lasts[j].first = lasts[j].second, lasts[j].second = i;
      if (arr[i] / j > MAX_GCD || j * j == arr[i]) continue;
      j = arr[i] / j;
      if (firsts[j].first < 0) firsts[j].first = i;
      else if (firsts[j].second < 0) firsts[j].second = i;
      lasts[j].first = lasts[j].second, lasts[j].second = i;
      j = arr[i] / j;
    }
  }
  tmax.resize(4 * n), tsum.resize(4 * n), lazy.resize(4 * n);
  for (int i = 0; i < n; ++i) update(1, 0, n - 1, i, i, i - 1);
  ll ans = 0;
  for (int i = MAX_GCD; i > 0; --i) {
    if (firsts[i].second < 0) continue;
    vector<pii> rems(3);
    rems[0] = {firsts[i].second + 1, n - 1}, rems[1] = {firsts[i].first + 1, lasts[i].second - 1}, rems[2] = {0, lasts[i].first - 1};
    for (pii rem : rems) {
      int lo = rem.first - 1, hi = rem.second + 1;
      while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (qmax(1, 0, n - 1, rem.first, mid) > rem.second) hi = mid;
        else lo = mid;
      }
      int rng = lo - rem.first + 1;
      ans += ((ll) rng * rem.second - qsum(1, 0, n - 1, rem.first, lo)) * i;
      update(1, 0, n - 1, rem.first, lo, rem.second);
    }
  }
  cout << ans << '\n';
  return 0;
}
