#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

struct st {

  vector<int> t;

  st(vector<pii>& arr, int n) {
    t.resize(2 * n);
    for (int i = 0; i < n; ++i) t[i + n] = arr[i].first;
    for (int i = n - 1; i > 0; --i) t[i] = min(t[2 * i], t[2 * i + 1]);
  }

  void upd(int p, int n) { for (t[p += n] = INT_MAX; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]); }

  int qry(int l, int r, int n) {
    int ans = INT_MAX;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = min(ans, t[l++]);
      if (r & 1) ans = min(ans, t[--r]);
    }
    return ans;
  }
};

inline void solve() {
  int n, k; cin >> n >> k;
  pii a; cin >> a.first >> a.second;
  vector<pii> arr(n - 1); for (int i = 0; i < n - 1; ++i) cin >> arr[i].first >> arr[i].second;
  sort(arr.begin(), arr.end(), [](const pii& x, const pii& y) {
    if (x.first + x.second != y.first + y.second) return x.first + x.second < y.first + y.second;
    return x.first < y.first;
  });
  if (a.first + a.second < k) {
    cout << "NO\n";
    return;
  }
  if (a.first >= k) {
    cout << "YES\n";
    return;
  }
  k -= a.second;
  for (int i = n - 2; i >= 0; --i) {
    if (arr[i].first >= k) {
      cout << "YES\n";
      return;
    }
    if (arr[i].first + arr[i].second < k) {
      cout << "NO\n";
      return;
    }
    if (i && arr[i - 1].first + arr[i - 1].second >= k) {
      cout << "YES\n";
      return;
    }
    k -= arr[i].second;
  }
  cout << "NO\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
