#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<pair<pii, pii>> orig;
vector<set<pair<pii, pii>>> info, gr;
vector<int> vals;

void dfs(int v) {
  while (info[v].size()) {
    pair<pii, pii> a = *info[v].begin();
    if (a.first.first > vals[v]) break;
    info[v].erase(info[v].begin());
    bool less = a.first.first < vals[v];
    if (!less) gr[v].insert(a);
    if (vals[a.second.first] >= a.second.second + less) continue;
    vals[a.second.first] = a.second.second + less;
    dfs(a.second.first);
  }
  while (gr[v].size()) {
    pair<pii, pii> a = *gr[v].begin();
    if (a.first.first >= vals[v]) return;
    gr[v].erase(gr[v].begin());
    if (vals[a.second.first] >= a.second.second + 1) continue;
    vals[a.second.first] = a.second.second + 1;
    dfs(a.second.first);
  }
}

int main() {
  int n, m, k; cin >> n >> m >> k;
  orig.resize(k), info.resize(n), gr.resize(n);
  for (int i = 0; i < k; ++i) {
    int x, a, y, b; cin >> x >> a >> y >> b;
    --x, --y;
    orig[i] = {{x, a}, {y, b}};
    info[x].insert({{a, i}, {y, b}});
    info[y].insert({{b, i}, {x, a}});
  }
  vals = vector<int>(n, 1);
  for (int i = 0; i < n; ++i) dfs(i);
  for (int i = 0; i < n; ++i) dfs(i);  
  ll sum = 0;
  for (int i = 0; i < n; ++i) {
    if (vals[i] > m) {
      cout << -1 << '\n';
      return 0;
    }
    sum += vals[i];
  }
  cout << sum << '\n';
  return 0;
}
