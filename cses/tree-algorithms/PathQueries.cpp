#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<vector<int>> adj;
vector<int> order, parent, m;
vector<bool> heavy;
vector<ll> t;
int n;

void update(int p, int v) { for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1]; }

ll query(int l, int r) {
  ll ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

void dfs(int v, int p) {
  parent[v] = p;
  for (int u : adj[v]) if (u != p) dfs(u, v);
  if (v) order.push_back(v);
}

void dfs(int v) {
  m[v] = order.size(), order.push_back(v);
  for (int u : adj[v]) if (u != parent[v] && heavy[u]) dfs(u);
  for (int u : adj[v]) if (u != parent[v] && !heavy[u]) dfs(u);
}

int main() {
  cin >> n;
  int q; cin >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  parent.resize(n); dfs(0, 0);
  vector<int> sizes(n, 1);
  for (int v : order) sizes[parent[v]] += sizes[v];
  heavy.resize(n); for (int i = 0; i < n; ++i) heavy[i] = sizes[i] > sizes[parent[i]] / 2;
  order.clear(), m.resize(n); dfs(0);
  vector<int> ps(n);
  int last = -1;
  for (int i = 0; i < n; ++i) {
    if (heavy[order[i]] && last < 0) last = i;
    else if (!heavy[order[i]]) last = -1;
    ps[i] = last;
  }
  t.resize(2 * n);
  for (int i = 0; i < n; ++i) update(m[i], arr[i]);
  for (int i = 0; i < q; ++i) {
    int type, a; cin >> type >> a; --a;
    if (type == 1) { int x; cin >> x; update(m[a], x); }
    else {
      ll ans = 0;
      a = m[a];
      while (a >= 0) {
        if (ps[a] == 0) ans += query(0, a + 1), a = -1;
        else if (heavy[order[a]]) ans += query(ps[a], a + 1), a = m[parent[order[ps[a]]]];
        else ans += t[a + n], a = m[parent[order[a]]];
      }
      cout << ans << '\n';
    }
  }
  return 0;
}

