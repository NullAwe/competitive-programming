#include <bits/stdc++.h>
using namespace std;

#define ll long long

void modify2(vector<ll>& t, int n, int p, ll value) {
  for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
}

ll query2(vector<ll>& t, int n, int l, int r) {
  ll res = LLONG_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res = min(res, t[l++]);
    if (r & 1) res = min(res, t[--r]);
  }
  return res;
}

void modify(vector<ll>& t, int n, int p, ll value) {
  for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
}

ll query(vector<ll>& t, int n, int l, int r) {
  ll res = LLONG_MIN;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res = max(res, t[l++]);
    if (r & 1) res = max(res, t[--r]);
  }
  return res;
}

int main() {
  int n, q; cin >> n >> q;
  vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  vector<ll> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
  // Stores prefix of a[i] - b[i] sums:
  vector<ll> pref(n + 1);
  for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i] - b[i];
  vector<ll> t(2 * n + 5);
  for (int i = 1; i < pref.size(); ++i) modify(t, n, i - 1, pref[i]);
  vector<ll> t2(2 * n + 5);
  for (int i = 1; i < pref.size(); ++i) modify2(t2, n, i - 1, pref[i]);
  for (int i = 0; i < q; ++i) {
    int l, r; cin >> l >> r;
    ll m = query(t, n, l - 1, r);
    ll before = pref[l - 1];
    if (m - before > 0 || pref[r] - before != 0) {
      cout << -1 << endl;
      continue;
    }
    // Output:
    cout << -(query2(t2, n, l - 1, r) - before) << endl;
  }
  return 0;
}