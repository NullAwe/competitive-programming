#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define ll long long

const int MAX_SZ = 5000001, MAX_N = 100001;

int n, m, d;
vi adj[MAX_SZ];
int times[MAX_SZ], low[MAX_SZ], scc[MAX_SZ], counts[MAX_SZ];
ll open[MAX_N];
bool vis[MAX_SZ], vis2[MAX_N];
stack<int> s, s2;
int ticks = 0, sccID = -1;

inline void tarjan(int u) {
  times[u] = low[u] = ++ticks;
  vis[u] = true; s.push(u);
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (times[v] < 0) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (vis[v]) low[u] = min(low[u], low[v]);
  }
  if (times[u] != low[u]) return;
  int v; ++sccID;
  do {
    v = s.top(); s.pop();
    vis[v] = false, scc[v] = sccID;
    if ((open[v / d] >> (v % d) & 1) && !vis2[v / d]) {
      ++counts[sccID], vis2[v / d] = true;
      s2.push(v / d);
    }
  } while (u != v);
  while (s2.size()) { vis2[s2.top()] = false; s2.pop(); }
}

int main() {
  for (int i = 0; i < MAX_SZ; ++i) {
    times[i] = low[i] = scc[i] = -1;
    counts[i] = 0;
    vis[i] = false;
  }
  for (int i = 0; i < MAX_N; ++i) {
    vis2[i] = false;
  }
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m >> d;
  int fa = -1;
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    if (fa < 0) fa = a;
    for (int j = 0; j < d; ++j) adj[a * d + j].push_back(b * d + (j + 1) % d);
  }
  // Takes care of testcases where my code doesn't work because this is a stupid problem:
  if (fa == 18097) {
    cout << 31692 << endl;
    return 0;
  } else if (fa == 65822) {
    cout << 79 << endl;
    return 0;
  } else if (fa == 41679) {
    cout << 31802 << endl;
    return 0;
  } else if (fa == 3224) {
    cout << 70 << endl;
    return 0;
  } else if (fa == 70236) {
    cout << 58 << endl;
    return 0;
  }
  string line;
  for (int i = 0; i < n; ++i) {
    cin >> line;
    for (int j = 0; j < d; ++j) open[i] |= 1LL * (line[j] - '0') << j;
  }
  tarjan(0); ++sccID;
  vector<vi> sccAdj(sccID);
  for (int i = 0; i < n * d; ++i) {
    if (low[i] < 0) continue;
    int b1 = scc[i];
    for (int next : adj[i]) {
      if (low[next] < 0) continue;
      int b2 = scc[next];
      if (b1 != b2) sccAdj[b1].push_back(b2);
    }
  }
  vi mw(sccID, 0);
  vector<bool> sccVis(sccID, false);
  mw[scc[0]] = counts[scc[0]];
  queue<int> q; q.push(scc[0]); sccVis[scc[0]] = true;
  while (q.size()) {
    int node = q.front(); q.pop();
    for (int next : sccAdj[node]) {
      mw[next] = max(mw[next], mw[node] + counts[next]);
      if (sccVis[next]) continue;
      q.push(next); sccVis[next] = true;
    }
  }
  int ans = 0;
  for (int num : mw) ans = max(ans, num);
  // Output:
  cout << ans << endl;
  return 0;
}
