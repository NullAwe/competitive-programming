#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<vector<int>> adj;
vector<int> order, pos, to;
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
  pos[v] = order.size();
  order.push_back(v);
  for (int u : adj[v]) if (u != p) dfs(u, v);
  to[v] = order.size();
}

int main() {
  cin >> n; t.resize(2 * n);
  int q; cin >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  adj = vector<vector<int>>(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  pos = vector<int>(n), to = vector<int>(n); dfs(0, 0);
  for (int i = 0; i < n; ++i) update(pos[i], arr[i]);
  for (int i = 0; i < q; ++i) {
    int type, a; cin >> type >> a; --a;
    if (type == 1) { int x; cin >> x; update(pos[a], x); }
    else cout << query(pos[a], to[a]) << '\n';
  }
  return 0;
}

