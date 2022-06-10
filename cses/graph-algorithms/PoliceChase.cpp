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
  
  set<int> get() {
    set<pii> ignore;
    for (FlowEdge edge : edges) {
      pii check = {edge.v, edge.u}; if (check.first > check.second) swap(check.first, check.second);
      if (edge.cap && edge.cap == edge.flow) ignore.insert(check);
    }
    vector<int> lvl(n, -1); lvl[0] = 0;
    queue<int> q; q.push(0);
    while (q.size()) {
      int v = q.front(); q.pop();
      for (int i : adj[v]) if (lvl[edges[i].u] < 0) lvl[edges[i].u] = lvl[v] + 1, q.push(edges[i].u);
    }
    set<int> s; for (pii p : ignore) s.insert(p.first), s.insert(p.second);
    set<int> vis; vis.insert(0);
    q.push(0);
    while (q.size()) {
      int v = q.front(); q.pop();
      for (int i : adj[v])
        if (((!s.count(edges[i].u) || !s.count(v)) && !vis.count(edges[i].u)) || (lvl[v] > lvl[edges[i].u])) vis.insert(edges[i].u), q.push(edges[i].u);
    }
    return vis;
  }
};
 
int main() {
  int n, m; cin >> n >> m; m <<= 1;
  vector<pair<ll, pii>> edges(m);
  for (int i = 0; i < (m >> 1); ++i) {
    int a, b, w; cin >> a >> b; --a, --b;
    edges[i] = {1, {a, b}};
    edges[i + (m >> 1)] = {1, {b, a}};
  }
  Dinic dinic(n, m, 0, n - 1, edges);
  cout << dinic.flow() << '\n';
  set<int> s = dinic.get();
  set<pii> has;
  for (pair<ll, pii> edge : edges) {
    int a = edge.second.first, b = edge.second.second;
    if (a > b) swap(a, b);
    if (has.count({a, b})) continue;
    if (s.count(a) ^ s.count(b)) cout << a + 1 << ' ' << b + 1 << '\n';
    has.insert({a, b});
  }
  return 0;
}
