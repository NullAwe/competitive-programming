#include <bits/stdc++.h>
using namespace std;

#define ll long long

void modify(vector<ll>& t, int n, int p, ll v) {
  for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
}

ll query(vector<ll>& t, int n, int l, int r) {
  ll ans = LLONG_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = min(ans, t[l++]);
    if (r & 1) ans = min(ans, t[--r]);
  }
  return ans;
}

int main() {
  int n, a, b; cin >> n >> a >> b;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<ll> p(n + 1); for (int i = 0; i < n; ++i) p[i + 1] = p[i] + arr[i];
  vector<ll> t(2 * n + 2, LLONG_MAX); for (int i = 0; i <= n; ++i) modify(t, n + 1, i, p[i]);
  ll ans = LLONG_MIN;
  for (int i = a; i <= n; ++i) ans = max(ans, p[i] - query(t, n + 1, max(i - b, 0), i - a + 1));
  cout << ans << '\n';
  return 0;
}
