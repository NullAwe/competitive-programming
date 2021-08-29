#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long

void modify(vector<int>& t, int n, int p, int value) {
  for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

ll query(vector<int>& t, int n, int l, int r) {
  ll res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res += t[l++];
    if (r & 1) res += t[--r];
  }
  return res;
}

int32_t main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Stores the local minimums:
  vector<int> minimums, t(2 * n + 5);
  minimums.push_back(0);
  modify(t, n, 0, 1);
  ll at = arr[0], ans = 0;
  for (int i = 1; i < n; ++i) {
    int newAt = at + pow(-1, i) * arr[i];
    if (newAt > at) {
      at = newAt;
      continue;
    }
    int lo = -1, hi = minimums.size();
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (minimums[mid] < newAt) lo = mid;
      else hi = mid;
    }
    ans += at - max(minimums[0] + 1, newAt);
    if (hi == minimums.size()) {
      modify(t, n, minimums.size(), 1);
      minimums.push_back(newAt);
    } else {
      ans += query(t, n, hi, minimums.size());
      if (minimums[hi] == newAt) {
        for (int i = hi + 1; i < minimums.size(); ++i) modify(t, n, i, 0);
        minimums.resize(hi + 1);
        modify(t, n, hi, query(t, n, hi, hi + 1) + 1);
      } else {
        for (int i = hi; i < minimums.size(); ++i) modify(t, n, i, 0);
        minimums.resize(hi + 1);
        minimums[hi] = newAt;
        modify(t, n, hi, 1);
      }
    }
    at = newAt;
  }
  // Output:
  cout << ans << endl;
  return 0;
}
