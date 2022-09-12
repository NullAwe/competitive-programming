#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>

const int SZ = 30;

vvi adj, spec, up;
vi lvl, tracker;
set<pii> edges;

void dfs(int v, int p, int l) {
  up[v][0] = p, lvl[v] = l;
  for (int u : adj[v]) if (u != p) dfs(u, v, l + 1);
}

int fnd(int a, int u) {
  for (int i = 0; i < SZ; ++i) if (u & (1 << i)) a = up[a][i];
  return a;
}

int bef(int a, int b) {
  if (lvl[b] < lvl[a] || fnd(b, lvl[b] - lvl[a]) != a) return up[a][0];
  return fnd(b, lvl[b] - lvl[a] - 1);
}

void add(int a, int b) {
  if (tracker[a] == INT_MAX || tracker[a] == b) return;
  if (tracker[a] >= 0) {
    edges.insert({a, tracker[a]});
    tracker[a] = INT_MAX;
    return;
  }
  for (int u : adj[a]) if (u != b) edges.insert({a, u});
  tracker[a] = b;
}

bool cycle(int v, vector<bool>& s) {
  if (s[v]) return true;
  if (tracker[v]) return false;
  s[v] = tracker[v] = 1;
  for (int u : adj[v]) if (lvl[u] > lvl[v] && cycle(u, s)) return true;
  for (int u : spec[v]) if (cycle(u, s)) return true;
  return s[v] = 0;
}

int main() {
  ifstream in("gathering.in");
  ofstream out("gathering.out");
  int n, m; in >> n >> m;
  adj.resize(n), spec.resize(n), up = vvi(n, vi(SZ)), lvl.resize(n), tracker = vi(n, -1);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; in >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  dfs(0, 0, 0);
  for (int i = 1; i < SZ; ++i) for (int j = 0; j < n; ++j) up[j][i] = up[up[j][i - 1]][i - 1];
  vector<bool> ans(n, 1);
  for (int i = 0; i < m; ++i) {
    int a, b; in >> a >> b; --a, --b;
    spec[b].push_back(a), add(a, bef(a, b)), ans[a] = 0;
  }
  set<pii> done = edges;
  queue<pii> q; for (pii edge : edges) q.push(edge);
  vector<set<int>> adj2(n); for (int i = 0; i < n; ++i) for (int num : adj[i]) adj2[i].insert(num);
  while (q.size()) {
    pii p = q.front(); q.pop();
    ans[p.first] = ans[p.second] = 0;
    set<int> rem = adj2[p.second];
    for (int u : adj2[p.second]) {
      if (u == p.first) continue;
      rem.erase(u);
      if (done.count({p.second, u})) continue;
      done.insert({p.second, u}), q.push({p.second, u});
    }
    adj2[p.second] = rem;
  }
  tracker = vi(n, 0);
  for (int i = 0; i < n; ++i) {
    if (ans[i]) {
      dfs(i, i, 0);
      vector<bool> s(n, 0);
      if (cycle(i, s)) ans = vector<bool>(n, 0);
      break;
    }
  }
  for (int num : ans) out << num << '\n';
  return 0;
}
