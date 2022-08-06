#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<pair<pii, pii>> ports;
vector<vector<int>> board;
vector<set<int>> ur, uc;

pii tp(pii p) {
  int ind = board[p.first][p.second];
  return ports[ind].first == p ? ports[ind].second : ports[ind].first;
}

void add(pii p, pii p2, int c) {
  board[p.first][p.second] = board[p2.first][p2.second] = c;
  ports[c] = {p, p2};
  ur[p.first].insert(p.second), ur[p2.first].insert(p2.second);
  uc[p.second].insert(p.first), uc[p2.second].insert(p2.first);
}

int main() {
  int n; cin >> n;
  vector<int> r(n), b(n);
  for (int i = 0; i < n; ++i) cin >> r[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  for (int i = 0; i < n; ++i) --r[i], --b[i];
  ports = vector<pair<pii, pii>>(n, {{-1, -1}, {-1, -1}});
  board = vector<vector<int>>(n, vector<int>(n, -1));
  ur.resize(n), uc.resize(n);
  for (int i = 0; i < n; ++i) ur[i].insert(-1), uc[i].insert(-1);
  int ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    pii pos = {r[i], n};
    while (pos.first > i || pos.second != i) {
      int next = *--ur[pos.first].lower_bound(pos.second);
      if (pos.first <= i && next <= i) pos.second = i;
      else pos = tp({pos.first, next});
    }
    pii pos2 = {n, b[i]};
    while (pos2.first != i || pos2.second > i) {
      int next = *--uc[pos2.second].lower_bound(pos2.first);
      if (pos2.second <= i && next <= i) pos2.first = i;
      else pos2 = tp({next, pos2.second});
    }
    if (pos == pos2) continue;
    add(pos, pos2, i);
    ++ans;
  }
  cout << ans << '\n';
  for (pair<pii, pii> pp : ports) {
    if (pp.first.first < 0) continue;
    cout << pp.first.first + 1 << ' ' << pp.first.second + 1 << ' ' << pp.second.first + 1 << ' ' << pp.second.second + 1 << '\n';
  }
  return 0;
}

