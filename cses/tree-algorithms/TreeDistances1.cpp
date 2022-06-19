#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<vector<int>> adj;
vector<pair<pii, pii>> ps;

void dfs(int v, int p) {
  ps[v] = {{v, 0}, {v, 0}};
  for (int u : adj[v]) {
    if (u == p) continue;
    dfs(u, v);
    if (ps[u].first.second >= ps[v].first.second) ps[v].second = ps[v].first, ps[v].first = {u, ps[u].first.second + 1};
    else if (ps[u].first.second >= ps[v].second.second) ps[v].second = {u, ps[u].first.second + 1};
  }
}

void dfs2(int v, int p) {
  if (v) {
    int dist = ps[p].first.first == v ? ps[p].second.second : ps[p].first.second;
    if (dist >= ps[v].first.second) ps[v].second = ps[v].first, ps[v].first = {p, dist + 1};
    else if (dist >= ps[v].second.second) ps[v].second = {p, dist + 1};
  }
  for (int u : adj[v]) if (u != p) dfs2(u, v);
}

int main() {
  int n; cin >> n;
  adj = vector<vector<int>>(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  ps = vector<pair<pii, pii>>(n); dfs(0, 0); dfs2(0, 0);
  for (int i = 0; i < n; ++i) cout << ps[i].first.second << ' ';
  cout << '\n';
  return 0;
}
