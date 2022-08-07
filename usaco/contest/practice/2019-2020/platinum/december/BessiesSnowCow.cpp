#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define ll long long

const int MAX_C = 1e5 + 1;

int n;
vector<vector<int>> adj;
vector<int> pre, sizes, order, qfrom, hpos, pars;
vector<pii> rngs;
vector<bool> heavy;
vector<vector<int>> ts;

int dfs(int v, int p) {
  int bef = pre.size();
  pre.push_back(v), sizes[v] = 1;
  for (int u : adj[v]) if (u != p) sizes[v] += dfs(u, v);
  rngs[v] = {bef, pre.size()};
  for (int u : adj[v]) if (u != p && sizes[u] * 2 >= sizes[v]) heavy[u] = true;
  return sizes[v];
}

void dfs(int v, int p, int f) {
  hpos[v] = order.size(), order.push_back(v), qfrom[v] = f;
  pars[v] = p;
  int pos = order.size() - 1;
  for (int u : adj[v]) if (u != p && heavy[u]) dfs(u, v, heavy[v] ? f : pos + 1);
  for (int u : adj[v]) if (u != p && !heavy[u]) dfs(u, v, pos);
}

struct HLD {

  vector<int> t;

  HLD() : t(2 * n) {}

  void modify(int p, int diff) {
    p = hpos[p];
    for (t[p += n] += diff; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }

  int query(int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans += t[l++];
      if (r & 1) ans += t[--r];
    }
    return ans;
  }

  int query(int v) {
    int ans = 0, pos = hpos[v];
    while (pos >= 0) {
      if (heavy[order[pos]]) {
        ans += query(qfrom[order[pos]], pos + 1);
        pos = hpos[pars[order[qfrom[order[pos]]]]];
      } else {
        ans += t[pos + n];
        pos = qfrom[order[pos]];
      }
    }
    return ans;
  }
};

struct Tracker {

  vector<set<int>> colors;
  vector<ll> t;
  HLD hld;

  Tracker() : colors(MAX_C), t(2 * n), hld() {}

  void modify(int p, int diff) {
    p = rngs[p].first;
    for (t[p += n] += diff * sizes[pre[p]]; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }
  
  ll query(int l, int r) {
    ll ans = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans += t[l++];
      if (r & 1) ans += t[--r];
    }
    return ans;
  }

  void add(int v, int c) {
    pii rng = rngs[v];
    set<int> copy = colors[c];
    bool par_ = false;
    for (int u : copy) {
      pii urng = rngs[u];
      if (rng.first <= urng.first && urng.second <= rng.second) {
        colors[c].erase(u);
        modify(u, -1);
        hld.modify(u, -1);
      } else if (urng.first <= rng.first && rng.second <= urng.second) {
        par_ = true;
      }
    }
    if (!par_) {
      colors[c].insert(v);
      modify(v, 1);
      hld.modify(v, 1);
    }
  }

  ll get(int v) {
    ll ans = sizes[v] * hld.query(v);
    pii rng = rngs[v];
    ans += query(rng.first + 1, rng.second);
    return ans;
  }
};

int main() {
  ifstream in("snowcow.in");
  ofstream out("snowcow.out");
  int q; in >> n >> q;
  adj.resize(n), pre.reserve(n), sizes.resize(n), rngs.resize(n), heavy.resize(n), qfrom.resize(n), hpos.resize(n), pars.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; in >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  dfs(0, 0), dfs(0, -1, -1);
  Tracker tracker;
  for (int i = 0; i < q; ++i) {
    int t, v; in >> t >> v;
    if (t == 1) {
      int c; in >> c;
      tracker.add(v - 1, c);
    } else {
      out << tracker.get(v - 1) << '\n';
    }
  }
  return 0;
}
