#include "Anthony.h"
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> Mark(int n, int m, int a, int b, vector<int> u, vector<int> v) {
  vector<vector<pii>> adj(n);
  for (int i = 0; i < m; ++i) adj[u[i]].push_back({v[i], i}), adj[v[i]].push_back({u[i], i});
  if (a == 2) {
    vector<int> color(m, -1), dist(n, -1), lp(n), llp(n);
    for (int i = 0; i < n; ++i) lp[i] = i, llp[i] = i;
    queue<int> q; q.push(0), dist[0] = 0;
    set<int> heads;
    while (q.size()) {
      int v = q.front(); q.pop();
      int label = dist[v] % 2;
      for (const auto& [u, i] : adj[v]) {
        if (color[i] >= 0) {
          if (adj[v].size() == 2) {
            lp[v] = lp[u];
            if (lp[u] == u) heads.insert(v);
            else llp[v] = llp[u];
          }
          continue;
        }
        color[i] = label;
        q.push(u), dist[u] = dist[v] + 1;
      }
    }
    vector<int> pat = {1, 1, 0, 0, 1, 0};
    vector<int> shifts(n);
    for (int p : heads) {
      int cur = p;
      while (true) {
        bool can = false;
        for (const auto& [u, i] : adj[cur]) {
          if (dist[u] > dist[cur] && adj[u].size() == 2) can = true, cur = u;
        }
        if (!can) break;
      }
      int v1 = dist[lp[p]] % 2, v2 = dist[cur] % 2;
      int dd = dist[cur] - dist[lp[p]];
      int shift = 0;
      if (dd % 6 == 0) shift = v1 ? 0 : 2;
      else if (dd % 6 == 1) shift = v1 ? 1 : 3;
      else if (dd % 6 == 2) shift = v1 ? 4 : 3;
      else if (dd % 6 == 3) shift = v1 ? 0 : 3;
      else if (dd % 6 == 4) shift = v1 ? 0 : 5;
      else shift = v1 ? 0 : 5;
      shifts[p] = shift;
    }
    for (int v = 1; v < n; ++v) {
      if (adj[v].size() != 2) continue;
      int p = lp[v];
      int shift = shifts[llp[v]];
      for (const auto& [u, i] : adj[v]) {
        if (dist[u] > dist[v]) {
          color[i] = pat[(dist[v] - dist[p] + shift) % 6];
        }
      }
    }
    return color;
  }
  vector<int> color(m, -1), dist(n, -1);
  queue<int> q; q.push(0), dist[0] = 0;
  while (q.size()) {
    int v = q.front(); q.pop();
    int label = dist[v] % 3;
    for (const auto& [u, i] : adj[v]) {
      if (color[i] >= 0) continue;
      color[i] = label;
      if (dist[u] < 0) q.push(u), dist[u] = dist[v] + 1;
    }
  }
  return color;
}
