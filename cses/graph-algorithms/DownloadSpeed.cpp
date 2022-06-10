#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

struct FlowEdge {
  
  int v, u;
  ll cap, flow;
  
  FlowEdge(int a, int b, ll c) { v = a, u = b, cap = c, flow = 0; }
};

struct Dinic {

  const ll INF = 1e18;
  
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  vector<int> level, p;
  queue<int> q;
  
  int n, m, s, t;
  
  Dinic(int size, int esize, int source, int sink, vector<pair<ll, pii>>& ed) {
    n = size, m = esize, s = source, t = sink;
    adj.resize(n), level.resize(n), p.resize(n);
    for (int i = 0; i < m; ++i) {
      int a = ed[i].second.first, b = ed[i].second.second; ll c = ed[i].first;
      edges.push_back(FlowEdge(a, b, c)), edges.push_back(FlowEdge(b, a, 0));
      adj[a].push_back(i * 2), adj[b].push_back(i * 2 + 1);
	}
  }
  
  bool bfs() {
    while (q.size()) {
      int v = q.front(); q.pop();
      for (int i : adj[v]) {
        if (!(edges[i].cap - edges[i].flow) || level[edges[i].u] >= 0) continue;
        level[edges[i].u] = level[v] + 1;
        q.push(edges[i].u);
      }
    }
    return level[t] != -1;
  }
  
  ll dfs(int v, ll pushed) {
    if (!pushed || v == t) return pushed;
    for (int& i = p[v]; i < adj[v].size(); ++i) {
      int id = adj[v][i], u = edges[id].u;
      if (level[v] + 1 != level[u] || !(edges[id].cap - edges[id].flow)) continue;
      ll _try = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (!_try) continue;
      edges[id].flow += _try;
      edges[id ^ 1].flow -= _try;
      return _try;
    }
    return 0;
  }
  
  ll flow() {
    ll f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1); level[s] = 0;
      q.push(s);
      if (!bfs()) break;
      fill(p.begin(), p.end(), 0);
      while (ll pushed = dfs(s, INF)) f += pushed;
    }
    return f;
  }
};

int main() {
  int n, m; cin >> n >> m;
  vector<pair<ll, pii>> edges(m);
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    edges[i] = {w, {a, b}};
  }
  Dinic dinic(n, m, 0, n - 1, edges);
  cout << dinic.flow() << '\n';
  return 0;
}
