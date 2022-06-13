#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<int> stl, str;
int n;

void ml(int v, int tl, int tr, int p, int val) {
  if (tl == tr) {
    stl[v] = val;
    return;
  }
  int m = (tl + tr) / 2;
  if (p <= m) ml(v << 1, tl, m, p, val);
  else ml((v << 1) + 1, m + 1, tr, p, val);
  stl[v] = min(stl[v << 1], stl[(v << 1) + 1] + m - tl + 1);
}

void ml(int p, int val) { ml(1, 0, n - 1, p, val); }

int ql(int v, int tl, int tr, int l, int r) {
  if (l > r || tl > tr) return INF;
  if (tl == l && tr == r) return stl[v];
  int m = (tl + tr) / 2;
  if (r <= m) return ql(v << 1, tl, m, l, r);
  if (l > m) return ql((v << 1) + 1, m + 1, tr, l, r);
  int vl = ql(v << 1, tl, m, l, m), vr = ql((v << 1) + 1, m + 1, tr, m + 1, r);
  return min(vl, vr + m - l + 1);
}

int ql(int l, int r) { return ql(1, 0, n - 1, l, r); }

void mr(int v, int tl, int tr, int p, int val) {
  if (tl == tr) {
    str[v] = val;
    return;
  }
  int m = (tl + tr) / 2;
  if (p <= m) mr(v << 1, tl, m, p, val);
  else mr((v << 1) + 1, m + 1, tr, p, val);
  str[v] = min(str[(v << 1) + 1], str[v << 1] + tr - m);
}

void mr(int p, int val) { mr(1, 0, n - 1, p, val); }

int qr(int v, int tl, int tr, int l, int r) {
  if (l > r || tl > tr) return INF;
  if (tl == l && tr == r) return str[v];
  int m = (tl + tr) / 2;
  if (r <= m) return qr(v << 1, tl, m, l, r);
  if (l > m) return qr((v << 1) + 1, m + 1, tr, l, r);
  int vl = qr(v << 1, tl, m, l, m), vr = qr((v << 1) + 1, m + 1, tr, m + 1, r);
  return min(vr, vl + r - m);
}

int qr(int l, int r) { return qr(1, 0, n - 1, l, r); }

int main() {
  cin >> n; stl.resize(3 * n), str.resize(3 * n);
  int q; cin >> q;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    ml(i, x); mr(i, x);
  }
  for (int i = 0; i < q; ++i) {
    int t, p; cin >> t >> p; --p;
    if (t == 1) {
      int x; cin >> x;
      ml(p, x); mr(p, x);
    } else {
      int a = qr(0, p), b = ql(p, n - 1);
      cout << min(a, b) << '\n';
    }
  }
  return 0;
}
