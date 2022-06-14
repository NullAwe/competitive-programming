#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<ll> t, lazy;
int n;

void push(int v, int l, int r) {
  int m = (l + r) / 2;
  t[v << 1] += lazy[v] * (m - l + 1);
  lazy[v << 1] += lazy[v];
  t[(v << 1) + 1] += lazy[v] * (r - m);
  lazy[(v << 1) + 1] += lazy[v];
  lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, ll add) {
  if (l > r) return;
  if (tl == l && tr == r) t[v] += add * (tr - tl + 1), lazy[v] += add;
  else {
    push(v, tl, tr);
    int m = (tl + tr) / 2;
    update(v << 1, tl, m, l, min(m, r), add);
    update((v << 1) + 1, m + 1, tr, max(m + 1, l), r, add);
    t[v] = t[v << 1] + t[(v << 1) + 1];
  }
}

ll query(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (tl == l && tr == r) return t[v];
  push(v, tl, tr);
  int m = (tl + tr) / 2;
  ll ans = query(v << 1, tl, m, l, min(m, r)) + query((v << 1) + 1, m + 1, tr, max(m + 1, l), r);
  return ans;
}

int main() {
  cin >> n; t.resize(3 * n), lazy.resize(3 * n);
  int q; cin >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<pii>> qs(n);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    qs[a].push_back({b, i});
  }
  stack<pii> s;
  vector<ll> ans(q);
  for (int i = n - 1; i >= 0; --i) {
    int last = i;
    while (s.size() && s.top().first < arr[i]) {
      update(1, 0, n - 1, last + 1, s.top().second, arr[i] - s.top().first);
      last = s.top().second;
      s.pop();
    }
    s.push({arr[i], last});
    for (pii p : qs[i]) ans[p.second] = query(1, 0, n - 1, i, p.first);
  }
  for (ll num : ans) cout << num << '\n';
  return 0;
}

