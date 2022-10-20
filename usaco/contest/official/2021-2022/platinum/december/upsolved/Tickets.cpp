#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pli pair<ll, int>
#define vp vector<pii>
#define vvp vector<vp>
#define vll vector<ll>

const ll INF = LLONG_MAX >> 1;

struct SegtreeGraph {

  int n, m;
  vvp rev;
  vll dists;

  SegtreeGraph(int n, int m) : n(n), m(m), rev((n << 1) + m), dists((n << 1) + m) {
    for (int i = n - 1; i > 0; --i) rev[i << 1].push_back({i, 0}), rev[(i << 1) ^ 1].push_back({i, 0});
  }

  inline void addEdges(int i, int v, int w, int l, int r) {
    rev[i += n << 1].push_back({v += n, w});
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) rev[l++].push_back({i, 0});
      if (r & 1) rev[--r].push_back({i, 0});
    }
  }

  void init(int src) {
    vll td((n << 1) + m, INF); td[src += n] = 0;
    set<pli> s; s.insert({0, src});
    while (s.size()) {
      pli first = *s.begin(); s.erase(s.begin());
      int v = first.second; ll d = first.first;
      for (pii next : rev[v]) {
        int u = next.first, w = next.second;
        if (d + w < td[u]) s.erase({td[u], u}), s.insert({td[u] = d + w, u});
      }
    }
    for (int i = 0; i < (n << 1) + m; ++i) dists[i] += td[i];
  }

  vll run() {
    init(0), init(n - 1);
    for (int i = 0; i < n; ++i) dists[i] = INF;
    for (int i = 0; i < (n << 1) + m; ++i) dists[i] = min(dists[i], INF);
    set<pli> s; for (int i = n; i < (n << 1) + m; ++i) s.insert({dists[i], i});
    while (s.size()) {
      pli first = *s.begin(); s.erase(s.begin());
      int v = first.second; ll d = first.first;
      for (pii next : rev[v]) {
        int u = next.first, w = next.second;
        if (d + w < dists[u]) s.erase({dists[u], u}), s.insert({dists[u] = d + w, u});
      }
    }
    vll ans(n); for (int i = 0; i < n; ++i) ans[i] = dists[i + n];
    return ans;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  SegtreeGraph graph(n, m);
  for (int i = 0; i < m; ++i) {
    int v, w, l, r; cin >> v >> w >> l >> r;
    graph.addEdges(i, v - 1, w, l - 1, r);
  }
  vll dists = graph.run();
  for (ll dist : dists) cout << (dist == INF ? -1 : dist) << '\n';
  return 0;
}
