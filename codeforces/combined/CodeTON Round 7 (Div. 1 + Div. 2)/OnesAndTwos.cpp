#include <bits/stdc++.h>
using namespace std;

#define ll long long

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
  int n, q; cin >> n >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  SumSegtree st(n); for (int i = 0; i < n; ++i) st.upd(i, arr[i]);
  set<int> ones;
  for (int i = 0; i < n; ++i) if (arr[i] == 1) ones.insert(i);
  for (int i = 0; i < q; ++i) {
    int t; cin >> t;
    if (t == 1) {
      int x; cin >> x;
      if (ones.empty()) {
        if (x % 2 == 0) cout << "YES\n";
        else cout << "NO\n";
        continue;
      }
      int first = *ones.begin();
      int mxsum = st.qry(first, n - 1);
      int last = *--ones.end();
      mxsum = max(mxsum, (int) st.qry(0, last));
      if (mxsum >= x) cout << "YES\n";
      else {
        int sum = st.qry(0, n - 1);
        if (sum >= x && sum % 2 == x % 2) cout << "YES\n";
        else cout << "NO\n";
      }
    } else {
      int p, v; cin >> p >> v; --p;
      if (v == 2 && arr[p] == 1) ones.erase(p);
      else if (v == 1 && arr[p] == 2) ones.insert(p);
      arr[p] = v;
      st.upd(p, v);
    }
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
