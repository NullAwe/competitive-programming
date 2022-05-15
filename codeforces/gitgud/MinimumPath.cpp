#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define ll long long

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  vector<vector<pair<int, ll>>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }
  vector<vector<ll>> dist(n, vector<ll>(4, -1)); dist[0][0] = 0;
  set<pair<ll, pair<int, int>>> q; q.insert({0, {0, 0}});
  while (q.size()) {
    pair<ll, pair<int, int>> top = *q.begin(); q.erase(q.begin());
    ll w = top.first;
    int v = top.second.first, k = top.second.second;
    for (pair<int, int> edge : adj[v]) {
      int u = edge.first, uw = edge.second;
      for (int i = 0; i < 4; ++i) {
        if (((k & 1) && !(i & 1)) || ((k & 2) && !(i & 2))) continue;
        ll tw = edge.second + w;
        if (!(k & 1) && (i & 1)) tw -= uw;
        if (!(k & 2) && (i & 2)) tw += uw;
        if (dist[u][i] < 0) {
          dist[u][i] = tw;
          q.insert({tw, {u, i}});
        } else if (dist[u][i] > tw) {
          q.erase({dist[u][i], {u, i}});
          dist[u][i] = tw;
          q.insert({tw, {u, i}});
        }
      }
    }
  }
  for (int i = 1; i < n; ++i) cout << dist[i][3] << ' ';
  cout << '\n';
  return 0;
}
