#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int sz = 30;

inline int query(int x, int k, int up[][sz]) {
  for (int ind = 0; ind < sz; ++ind) if (k & (1 << ind)) x = up[x][ind];
  return x;
}

int main() {
  int n, q; cin >> n >> q;
  int up[n][sz];
  for (int i = 0; i < n; ++i) cin >> up[i][0];
  for (int i = 0; i < n; ++i) --up[i][0];
  for (int j = 1; j < sz; ++j) for (int i = 0; i < n; ++i) up[i][j] = up[up[i][j - 1]][j - 1];
  vector<pair<int, pii>> cycle(n);
  vector<int> state(n, -1);
  for (int i = 0; i < n; ++i) {
    if (state[i] > 0) continue;
    vector<int> p; int cur;
    for (cur = i; state[cur] < 0; p.push_back(cur), state[cur] = 0, cur = up[cur][0]);
    if (!state[cur]) {
      vector<int> group;
      while (p.back() != cur) group.push_back(p.back()), p.pop_back();
      group.push_back(p.back()), p.pop_back();
      for (int j = 0; j < group.size(); ++j) cycle[group[j]] = {i + 1, {group.size() - j, group.size()}};
      for (int num : group) state[num] = 1;
    }
    for (int num : p) state[num] = 1;
  }
  vector<int> dr(n), r(n);
  for (int i = 0; i < n; ++i) if (cycle[i].first) r[i] = i;
  for (int i = 0; i < n; ++i) {
    if (cycle[i].first || dr[i]) continue;
    vector<int> p;
    for (int cur = i; !cycle[cur].first && !dr[cur]; p.push_back(cur), cur = up[cur][0]);
    for (int j = p.size() - 1; j >= 0; --j) dr[p[j]] = dr[up[p[j]][0]] + 1, r[p[j]] = r[up[p[j]][0]];
  }
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    if (a == b) {
      cout << 0 << '\n';
      continue;
    }
    int add = 0;
    if (cycle[a].first && !cycle[b].first) {
      cout << -1 << '\n';
      continue;
    }
    if (!cycle[a].first && !cycle[b].first) {
      if (r[a] != r[b] || dr[a] <= dr[b] || query(a, dr[a] - dr[b], up) != b) cout << -1 << '\n';
      else cout << dr[a] - dr[b] << '\n';
      continue;
    }
    if (!cycle[a].first) add = dr[a], a = r[a];
    if (cycle[a].first != cycle[b].first) cout << -1 << '\n';
    else {
      int ai = cycle[a].second.first, bi = cycle[b].second.first;
      if (ai > bi) bi += cycle[b].second.second;
      cout << add + bi - ai << '\n';
    }
  }
  return 0;
}
