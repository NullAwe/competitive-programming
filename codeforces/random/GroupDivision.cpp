#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<bool> vis;
vector<int> lv, hb;
vector<vector<int>> adj;

void dfs(int v, int l) {
  vis[v] = true, lv[v] = l;
  for (int u : adj[v]) if (!vis[u]) dfs(u, l + 1);
}

int dfs2(int v) {
  hb[v] = INT_MAX;
  for (int u : adj[v]) if (lv[u] == lv[v] + 1) hb[v] = min(hb[v], dfs2(u));
  int mn = INT_MAX;
  for (int u : adj[v]) if (lv[u] < lv[v] - 1) mn = min(mn, lv[u]);
  return min(mn, hb[v]);
}

inline void solve() {
  int n1, n2, m; cin >> n1 >> n2 >> m;
  adj.clear(), vis.clear(), lv.clear(), hb.clear();
  adj.resize(n1 + n2), vis.resize(n1 + n2), lv.resize(n1 + n2), hb.resize(n1 + n2);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  dfs(0, 0); dfs2(0);
  vector<vector<int>> radj(n1 + n2);
  for (int i = 0; i < n1 + n2; ++i) {
    int best = -1;
    for (int v : adj[i]) {
      if (abs(lv[i] - lv[v]) <= 1) radj[i].push_back(v);
      if (lv[v] < lv[i]) {
        if (best == -1) best = v;
        if (lv[v] < lv[best]) best = v;
      }
    }
    if (lv[best] >= hb[i]) best = -1;
    if (best >= 0) radj[i].push_back(best), radj[best].push_back(i);
  }
  adj = radj;
  set<pii> s; s.insert({lv[0], 0});
  set<int> s1;
  vector<bool> vis2(n1 + n2); vis2[0] = true;
  while (s.size() && (int) s1.size() < n1) {
    pii v = *--s.end(); s.erase(v);
    s1.insert(v.second);
    for (int u : adj[v.second]) {
      if (vis2[u]) continue;
      vis2[u] = true;
      s.insert({lv[u], u});
    }
  }
  for (int num : s1) cout << num + 1 << ' ';
  cout << '\n';
  for (int i = 0; i < n1 + n2; ++i) if (!s1.count(i)) cout << i + 1 << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
