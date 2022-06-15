#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>

const int MAX_N = 4e5;

vector<pll> t(MAX_N * 2);

void update(int v, int tl, int tr, int p, int val) {
  if (tl == tr) t[v] = {val, val};
  else {
    int mid = (tl + tr) / 2;
    if (p <= mid) update(v << 1, tl, mid, p, val);
    else update((v << 1) + 1, mid + 1, tr, p, val);
    t[v].first = max(t[v << 1].first, t[v << 1].second + t[(v << 1) + 1].first);
    t[v].second = t[v << 1].second + t[(v << 1) + 1].second;
  }
}

pll query(int v, int tl, int tr, int l, int r, ll add) {
  if (tl == l && tr == r) return {t[v].first + add, t[v].second};
  int mid = (tl + tr) / 2;
  if (r <= mid) return query(v << 1, tl, mid, l, r, add);
  if (l > mid) return query((v << 1) + 1, mid + 1, tr, l, r, add);
  pll ln = query(v << 1, tl, mid, l, mid, add), rn = query((v << 1) + 1, mid + 1, tr, mid + 1, r, add + ln.second);
  return {max(ln.first, rn.first), ln.second + rn.second};
}

int main() {
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    update(1, 0, n - 1, i, x);
  }
  for (int i = 0; i < q; ++i) {
    int type, a, b; cin >> type >> a >> b;
    if (type == 1) update(1, 0, n - 1, a - 1, b);
    else cout << max(query(1, 0, n - 1, a - 1, b - 1, 0).first, 0LL) << '\n';
  }
  return 0;
}

