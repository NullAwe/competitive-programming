#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<vector<pii>> adj, rev, sccAdj;
vector<bool> used;
vector<int> order, component, belong, roots;

void dfs1(int v) {
  used[v] = true;
  for (pii u : adj[v]) if (!used[u.first]) dfs1(u.first);
  order.push_back(v);
}

void dfs2(int v) {
  used[v] = true;
  component.push_back(v);
  for (pii u : rev[v]) if (!used[u.first]) dfs2(u.first);
}

void dfs3(int v) {
  used[v] = true;
  for (pii u : adj[v]) if (!used[u.first] && belong[v] == belong[u.first]) sccAdj[v].push_back(u), dfs3(u.first);
}

ll GCD(ll a, ll b) { return b == 0 ? a : GCD(b, a % b); }

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  adj.resize(n), rev.resize(n), used.resize(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c; cin >> a >> b >> c; --a, --b;
    adj[a].push_back({b, c});
    rev[b].push_back({a, c});
  }
  for (int i = 0; i < n; ++i) if (!used[i]) dfs1(i);
  used.clear(), used.resize(n), belong.resize(n);
  reverse(order.begin(), order.end());
  for (int v : order) {
    if (used[v]) continue;
    dfs2(v);
    for (int num : component) belong[num] = roots.size();
    roots.push_back(v);
    component.clear();
  }
  used.clear(), used.resize(n), sccAdj.resize(n);
  for (int v : order) if (!used[v]) dfs3(v);
  vector<ll> dists(n, -1); for (int num : roots) dists[num] = 0;
  queue<int> q; for (int num : roots) q.push(num);
  while (q.size()) {
    int v = q.front(); q.pop();
    for (pii u : sccAdj[v]) {
      if (dists[u.first] >= 0) continue;
      dists[u.first] = dists[v] + u.second;
      q.push(u.first);
    }
  }
  vector<ll> gcds(roots.size());
  for (int v = 0; v < n; ++v) for (pii u : adj[v])
    if (belong[v] == belong[u.first]) gcds[belong[v]] = GCD(gcds[belong[v]], dists[v] + u.second - dists[u.first]);
  int c; cin >> c;
  for (int i = 0; i < c; ++i) {
    int v, s, t; cin >> v >> s >> t; --v;
    cout << (s % GCD(t, gcds[belong[v]]) ? "NO\n" : "YES\n");
  }
  return 0;
}

