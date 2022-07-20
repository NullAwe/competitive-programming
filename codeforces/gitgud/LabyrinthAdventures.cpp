#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<pii> ud, rd;

vector<ll> tuu, tur, tru, trr, uu, ur, ru, rr;
int n;

inline int dist(pii a, pii b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

void build(int v, int tl, int tr) {
  if (tl == tr) {
    tuu[v] = uu[tl], tur[v] = ur[tl], tru[v] = ru[tl], trr[v] = rr[tl];
    return;
  }
  int m = (tl + tr) / 2;
  build(2 * v, tl, m), build(2 * v + 1, m + 1, tr);
  tuu[v] = min(tuu[2 * v] + tuu[2 * v + 1], tur[2 * v] + tru[2 * v + 1]);
  tur[v] = min(tuu[2 * v] + tur[2 * v + 1], tur[2 * v] + trr[2 * v + 1]);
  tru[v] = min(tru[2 * v] + tuu[2 * v + 1], trr[2 * v] + tru[2 * v + 1]);
  trr[v] = min(tru[2 * v] + tur[2 * v + 1], trr[2 * v] + trr[2 * v + 1]);
}

vector<ll> query(int v, int tl, int tr, int l, int r) {
  vector<ll> ans(4);
  if (tl == l && tr == r) {
    ans[0] = tuu[v], ans[1] = tur[v], ans[2] = tru[v], ans[3] = trr[v];
    return ans;
  }
  int m = (tl + tr) / 2;
  if (r <= m) return query(2 * v, tl, m, l, r);
  else if (l > m) return query(2 * v + 1, m + 1, tr, l, r);
  vector<ll> a = query(2 * v, tl, m, l, min(m, r)),
            b = query(2 * v + 1, m + 1, tr, max(m + 1, l), r);
  ans[0] = min(a[0] + b[0], a[1] + b[2]);
  ans[1] = min(a[0] + b[1], a[1] + b[3]);
  ans[2] = min(a[2] + b[0], a[3] + b[2]);
  ans[3] = min(a[2] + b[1], a[3] + b[3]);
  return ans;
}

inline ll query(pii p1, pii p2) {
  int l1 = max(p1.first, p1.second), l2 = max(p2.first, p2.second);
  if (l1 == l2) return dist(p1, p2);
  if (l1 > l2) swap(p1, p2), swap(l1, l2);
  int su = dist(ud[l1], p1), sr = dist(rd[l1], p1),
      eu = dist({ud[l2 - 1].first + 1, ud[l2 - 1].second}, p2),
      er = dist({rd[l2 - 1].first, rd[l2 - 1].second + 1}, p2);
  if (l1 + 1 == l2) return min(su + eu, sr + er) + 1;
  vector<ll> dists = query(1, 0, n - 1, l1 + 1, l2 - 1);
  return min(min(su + eu + query(1, 0, n - 1, l1 + 1, l2 - 1)[0],
                su + er + query(1, 0, n - 1, l1 + 1, l2 - 1)[1]),
            min(sr + eu + query(1, 0, n - 1, l1 + 1, l2 - 1)[2],
                sr + er + query(1, 0, n - 1, l1 + 1, l2 - 1)[3])) + 1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n; --n;
  ud.resize(n); rd.resize(n);
  tuu.resize(4 * n), tur.resize(4 * n), tru.resize(4 * n), trr.resize(4 * n);
  uu.resize(n), ur.resize(n), ru.resize(n), rr.resize(n);
  pii l1 = {-1, 0}, l2 = {0, -1};
  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2; --x1, --y1, --x2, --y2;
    pii p1 = {x1, y1}, p2 = {x2, y2};
    ++l1.first, ++l2.second;
    uu[i] = dist(l1, p1) + 1, ur[i] = dist(l1, p2) + 1, ru[i] = dist(l2, p1) + 1, rr[i] = dist(l2, p2) + 1;
    l1 = p1, l2 = p2;
    ud[i] = p1, rd[i] = p2;
  }
  build(1, 0, n - 1);
  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2; --x1, --y1, --x2, --y2;
    cout << query({x1, y1}, {x2, y2}) << '\n';
  }
  return 0;
}
