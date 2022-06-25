#include <bits/stdc++.h>
using namespace std;

vector<int> t, t2;
int n;

void mmax(int p, int v) { for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]); }

int qmax(int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = max(ans, t[l++]);
    if (r & 1) ans = max(ans, t[--r]);
  }
  return ans;
}

void mmin(int p, int v) { for (t2[p += n] = v; p > 1; p >>= 1) t2[p >> 1] = min(t2[p], t2[p ^ 1]); }

int qmin(int l, int r) {
  int ans = INT_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = min(ans, t2[l++]);
    if (r & 1) ans = min(ans, t2[--r]);
  }
  return ans;
}

int id(int p, int v, bool big) {
  int lo = p, hi = n;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    if (big) {
      if (qmax(p, mid + 1) > v) hi = mid;
      else lo = mid;
    } else {
      if (qmin(p, mid + 1) < v) hi = mid;
      else lo = mid;
    }
  }
  return hi;
}

void solve() {
  cin >> n; t.resize(2 * n); t2.resize(2 * n);
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) mmin(i, arr[i]), mmax(i, arr[i]);
  int at = 0, moves = 0;
  while (at < n - 1) {
    ++moves;
    int l = min(arr[at + 1], arr[at]), r = max(arr[at], arr[at + 1]);
    bool up = arr[at + 1] > arr[at];
    ++at;
    while (at < n - 1) {
      int pu = id(at, r, true), pd = id(at, l, false);
      if (min(pu, pd) == n) break;
      if ((pu > pd) ^ up) {
        if (pu < pd) r = arr[pu];
        else l = arr[pd];
        at = min(pu, pd);
      } else break;
    }
  }
  cout << moves << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
