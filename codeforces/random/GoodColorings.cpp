#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int MAX_N = 1001;

int grid[MAX_N][MAX_N];

void solve() {
  int n; cin >> n;
  set<pii> arr;
  vector<set<int>> rows(n), cols(n);
  for (int i = 0; i < 2 * n; ++i) {
    int x, y; cin >> x >> y; --x, --y;
    arr.insert({x, y});
    grid[x][y] = i + 1;
    rows[x].insert(y);
    cols[y].insert(x);
  }
  // get rid of all useless rows
  queue<pii> todo; // 0 = row, 1 = col
  for (int i = 0; i < n; ++i) {
    if (rows[i].size() < 2) todo.push({i, 0});
    if (cols[i].size() < 2) todo.push({i, 1});
  }
  while (todo.size()) {
    pii top = todo.front(); todo.pop();
    if (top.second == 0) {
      if (rows[top.first].empty()) continue;
      int y = *rows[top.first].begin(); rows[top.first].clear();
      cols[y].erase(top.first);
      if (cols[y].size() < 2) todo.push({y, 1});
    } else {
      if (cols[top.first].empty()) continue;
      int x = *cols[top.first].begin(); cols[top.first].clear();
      rows[x].erase(top.first);
      if (rows[x].size() < 2) todo.push({x, 0});
    }
  }
  // reshuffle useful rows into a good pattern:
  vector<int> lst;
  for (int i = 0; i < n; ++i) if (rows[i].size()) lst.push_back(i);
  int nn = lst.size();
  set<int> has;
  set<int> colls;
  vector<int> ro(nn), co(nn);
  int cr = -1, cc = -1, cnt = 0;
  vector<int> crs;
  for (int i = 0; i < nn; ++i) {
    if (cr == -1 || cc == -1) {
      cr = lst[0];
      cc = *rows[lst[0]].begin();
    }
    if (has.count(cr)) {
      for (int j = 0; j < i; ++j) {
        if (ro[j] == cr) {
          for (int k = j; k < i; ++k) {
            ro[k - j] = ro[k];
            co[k - j] = co[k];
          }
          co[0] = cc;
          cnt = i - j;
          break;
        }
      }
      break;
    }
    ++cnt;
    ro[i] = cr;
    co[i] = cc;
    has.insert(cr);
    crs.push_back(cr);
    if (cc == *rows[cr].begin()) cc = *--rows[cr].end();
    else cc = *rows[cr].begin();
    if (cr == *cols[cc].begin()) cr = *--cols[cc].end();
    else cr = *cols[cc].begin();
  }
  nn = cnt;
  // binary search:
  vector<pii> nxts;
  while (nn > 2) {
    int mid = nn / 2;
    int x = ro[mid], y = co[mid];
    cout << "? " << x + 1 << ' ' << co[0] + 1 << endl;
    int res; cin >> res;
    bool has = grid[x][y] == res;
    for (int i = 0; i < mid; ++i)
      has |= grid[ro[i]][co[i]] == res | grid[ro[i]][co[i + 1]] == res;
    grid[x][co[0]] = res;
    nxts.push_back({x, co[0]});
    if (has) {
      for (int i = mid; i < nn; ++i) {
        ro[i - mid] = ro[i];
        if (i > mid) co[i - mid] = co[i];
      }
      nn = nn - mid;
    } else nn = mid + 1;
  }
  cout << "! " << ro[0] + 1 << ' ' << ro[1] + 1 << ' ' << co[0] + 1 << ' ' << co[1] + 1 << endl;
  for (pii p : arr) {
    grid[p.first][p.second] = 0;
  }
  for (pii p : nxts) {
    grid[p.first][p.second] = 0;
  }
  string res; cin >> res;
  if (res[0] == 'E') exit(0);
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}