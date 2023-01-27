#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int INF = 1000000007;

struct Tracker {

  set<pii> has;

  set<int> rows, cols;
  map<int, int> mrows, mcols;

  set<pair<pii, pii>> starts;

  Tracker() {}

  void add(int x, int y) {
    has.insert({x, y});
    if (!rows.count(x)) {
      rows.insert(x);
      mrows[x] = y;
    }
    mrows[x] = min(mrows[x], y);
    if (!cols.count(y)) {
      cols.insert(y);
      mcols[y] = x;
    }
    mcols[y] = min(mcols[y], x);
  }

  pii find(int x, int y) {
    while (true) {
      int bx = x, by = y;
      while (rows.count(x) && mrows[x] <= y) ++x;
      while (cols.count(y) && mcols[y] <= x) ++y;
      if (bx == x && by == y) break;
    }
    return {x, y};
  }

  void build() {
    pii cur = find(0, 0);
    while (true) {
      int sx = cur.first, sy = cur.second;
      bool none = false;
      while (true) {
        auto itx = rows.upper_bound(sx);
        auto ity = cols.upper_bound(sy);
        if (itx == rows.end() && ity == cols.end()) {
          none = true;
          break;
        }
        if (itx == rows.end() || (ity != cols.end() && *ity - cur.second <= *itx - cur.first)) {
          int ny = *ity, nx = cur.first + (ny - cur.second);
          if (mcols[ny] <= nx) {
            sx = nx, sy = ny;
            break;
          }
          sy = ny;
        } else {
          int nx = *itx, ny = cur.second + (nx - cur.first);
          if (mrows[nx] <= ny) {
            sx = nx, sy = ny;
            break;
          }
          sx = nx;
        }
      }
      if (none) {
        starts.insert({cur, {cur.first + INF, cur.second + INF}});
        break;
      }
      starts.insert({cur, {sx, sy}});
      cur = find(sx, sy);
    }
  }

  bool winning(int x, int y) {
    if (has.count({x, y})) return 0;
    if (rows.count(x) && mrows[x] <= y) return 1;
    if (cols.count(y) && mcols[y] <= x) return 1;
    auto it = starts.upper_bound({{x, y}, {INT_MAX, INT_MAX}});
    if (it == starts.begin()) return 1;
    auto bef = *prev(it);
    if (x - bef.first.first == y - bef.first.second &&
        x < bef.second.first && y < bef.second.second) return 0;
    return 1;
  }
};

int main() {
  int n, m; cin >> n >> m;
  Tracker tr;
  tr.add(0, 0);
  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    tr.add(x, y);
  }
  tr.build();
  for (int i = 0; i < m; ++i) {
    int x, y; cin >> x >> y;
    cout << (tr.winning(x, y) ? "WIN" : "LOSE") << '\n';
  }
  return 0;
}
