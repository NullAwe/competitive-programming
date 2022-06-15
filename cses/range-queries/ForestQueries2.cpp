#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> t;
int n;

inline void my(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y) {
  if (ly == ry) {
    if (lx == rx) t[vx][vy] = 1 - t[vx][vy];
    else t[vx][vy] = t[vx << 1][vy] + t[(vx << 1) + 1][vy];
  } else {
    int m = (ly + ry) / 2;
    if (y <= m) my(vx, lx, rx, vy << 1, ly, m, x, y);
    else my(vx, lx, rx, (vy << 1) + 1, m + 1, ry, x, y);
    t[vx][vy] = t[vx][vy << 1] + t[vx][(vy << 1) + 1];
  }
}

inline void mx(int v, int tl, int tr, int x, int y) {
  if (tl < tr) {
    int m = (tl + tr) / 2;
    if (x <= m) mx(v << 1, tl, m, x, y);
    else mx((v << 1) + 1, m + 1, tr, x, y);
  }
  my(v, tl, tr, 1, 0, n - 1, x, y);
}

inline int qy(int vx, int vy, int tl, int tr, int y1, int y2) {
  if (y1 > y2) return 0;
  if (tl == y1 && tr == y2) return t[vx][vy];
  int m = (tl + tr) / 2;
  return qy(vx, vy << 1, tl, m, y1, min(m, y2)) + qy(vx, (vy << 1) + 1, m + 1, tr, max(m + 1, y1), y2);
}

inline int qx(int v, int tl, int tr, int x1, int x2, int y1, int y2) {
  if (x1 > x2) return 0;
  if (v == 0) exit(0);
  if (tl == x1 && tr == x2) return qy(v, 1, 0, n - 1, y1, y2);
  int m = (tl + tr) / 2;
  return qx(v << 1, tl, m, x1, min(m, x2), y1, y2) + qx((v << 1) + 1, m + 1, tr, max(m + 1, x1), x2, y1, y2);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int q; cin >> n >> q;
  t.resize(4 * n); for (int i = 0; i < 4 * n; ++i) t[i].resize(4 * n);
  for (int i = 0; i < n; ++i) {
    string str; cin >> str;
    for (int j = 0; j < n; ++j) if (str[j] == '*') mx(1, 0, n - 1, i, j);
  }
  for (int i = 0; i < q; ++i) {
    int type, x1, y1; cin >> type >> x1 >> y1; --x1, --y1;
    if (type == 1) mx(1, 0, n - 1, x1, y1);
    else {
      int x2, y2; cin >> x2 >> y2; --x2, --y2;
      cout << qx(1, 0, n - 1, x1, x2, y1, y2) << '\n';
    }
  }
  return 0;
}

