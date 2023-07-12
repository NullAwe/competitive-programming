#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MAX_N = 100001;
const int LG = 17;
const int LG2 = 40;

int n;
vector<vector<int>> adj;
map<pii, int> m;

int _p[MAX_N], _l[MAX_N], up[LG][MAX_N];

void dfs(int v, int p, int l) {
  _p[v] = p, _l[v] = l;
  for (int u : adj[v]) if (u != p) dfs(u, v, l + 1);
}

inline int jmp(int a, int u) {
  for (int i = 0; i < LG; ++i) if (u & (1 << i)) a = up[i][a];
  return a;
}

inline int lca(int a, int b) {
  if (_l[a] > _l[b]) swap(a, b);
  b = jmp(b, _l[b] - _l[a]);
  for (int i = LG - 1; i >= 0; --i)
    if (up[i][a] != up[i][b]) a = up[i][a], b = up[i][b];
  return a == b ? a : up[0][a];
}

inline void solve() {
  cin >> n; adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b); adj[b].push_back(a);
    m[{a, b}] = i, m[{b, a}] = i;
  }
  dfs(0, 0, 0);
  for (int i = 0; i < n; ++i) up[0][i] = _p[i];
  for (int i = 1; i < LG; ++i) for (int j = 0; j < n; ++j) up[i][j] = up[i - 1][up[i - 1][j]];
  vector<ll> arr(n - 1), nums(n);
  for (int i = 0; i < n - 1; ++i) cin >> arr[i];
  vector<ll> save = arr;
  for (int bit = 0; bit < LG2; ++bit) {
    vector<int> prt(n), rprt(n);
    for (int i = 0; i < n - 1; ++i)
      prt[i + 1] = (arr[i] & 1) ^ (prt[i] & 1);
    queue<int> q; q.push(0);
    while (q.size()) {
      int v = q.front(); q.pop();
      for (int u : adj[v]) {
        if (u == _p[v]) continue;
        q.push(u);
        nums[u] += (1LL << bit) * (rprt[u] = prt[u] ^ prt[v]);
      }
    }
    vector<ll> sum(n);
    q.push(0);
    while (q.size()) {
      int v = q.front(); q.pop();
      for (int u : adj[v]) {
        if (u == _p[v]) continue;
        q.push(u);
        sum[u] = sum[v] + rprt[u];
      }
    }
    for (int i = 0; i < n - 1; ++i) {
      arr[i] -= sum[i] + sum[i + 1] - 2 * sum[lca(i, i + 1)];
      arr[i] /= 2;
    }
  }
  for (int i = 1; i < n; ++i) {
    if (nums[i] == 0 || nums[i] > 1000000LL * 1000000LL) {
      cout << -1 << '\n';
      return;
    }
  }
  vector<ll> sum(n);
  queue<int> q; q.push(0);
  while (q.size()) {
    int v = q.front(); q.pop();
    for (int u : adj[v]) {
      if (u == _p[v]) continue;
      q.push(u);
      sum[u] = sum[v] + nums[u];
    }
  }
  for (int i = 0; i < n - 1; ++i) {
    if (sum[i] + sum[i + 1] - 2 * sum[lca(i, i + 1)] != save[i]) {
      cout << -1 << '\n';
      return;
    }
  }
  vector<ll> ans(n - 1);
  for (int i = 1; i < n; ++i) ans[m[{i, _p[i]}]] = nums[i];
  for (ll num : ans) cout << num << '\n';
}

int main() {
  int t = 1;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
