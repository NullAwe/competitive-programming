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

  Dinic(int size, int esize, int source, int sink, vector<pair<ll, pii>>& eds) {
    n = size, m = esize, s = source, t = sink;
    adj.resize(n), level.resize(n), p.resize(n);
    for (int i = 0; i < m; ++i) {
      int a = eds[i].second.first, b = eds[i].second.second; ll c = eds[i].first;
      edges.push_back(FlowEdge(a, b, c));
      edges.push_back(FlowEdge(b, a, 0));
      adj[a].push_back(2 * i);
      adj[b].push_back(2 * i + 1);
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

  vector<pii> get() {
    vector<pii> ans;
    for (FlowEdge edge : edges) if (edge.v > 0 && edge.u < n - 1 && edge.v < edge.u && !(edge.cap - edge.flow)) ans.push_back({edge.v, edge.u});
    return ans;
  }
};

const vector<int> dx = {0, 0, -1, 1}, dy = {-1, 1, 0, 0};

int main() {
  int n, m; cin >> n >> m;
  int ans = 0;
  vector<string> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
    for (int j = 0; j < m; ++j) ans += arr[i][j] == '#';
  }
  vector<pair<ll, pii>> edges;
  int size = 2;
  int source, sink;
  vector<int> a, b;
  int id = 0;
  vector<vector<int>> down(n, vector<int>(m, -1));
  vector<vector<int>> right(n, vector<int>(m, -1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (arr[i][j] == '.') continue;
      vector<int> ids(4, -1);
      for (int d = 1; d < 4; d += 2) {
        int x = i + dx[d], y = j + dy[d];
        if (x < 0 || y < 0 || x >= n || y >= m || arr[x][y] == '.') continue;
        ++size, ids[d] = id++;
        if (d < 2) {
          a.push_back(ids[d]), right[i][j] = ids[d];
          if (i - 1 >= 0 && down[i - 1][j] >= 0) edges.push_back({1, {ids[d], down[i - 1][j]}});
          if (i - 1 >= 0 && j + 1 < m && down[i - 1][j + 1] >= 0) edges.push_back({1, {ids[d], down[i - 1][j + 1]}});
        } else {
          b.push_back(ids[d]), down[i][j] = ids[d];
          if (j - 1 >= 0 && right[i][j - 1] >= 0) edges.push_back({1, {right[i][j - 1], ids[d]}});
          if (ids[1] >= 0) edges.push_back({1, {ids[1], ids[d]}});
        }
      }
    }
  }
  for (int num : a) edges.push_back({1, {id, num}});
  for (int num : b) edges.push_back({1, {num, id + 1}});
  Dinic dinic(size, edges.size(), id, id + 1, edges);
  int flow = dinic.flow();
  ans -= ((size - 2) - flow);
  cout << ans << '\n';
  return 0;
}
