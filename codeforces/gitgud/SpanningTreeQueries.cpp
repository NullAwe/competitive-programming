#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<int> parent;
int val;

int find(int v) {
  if (v == parent[v]) return v;
  return parent[v] = find(parent[v]);
}

void link(int a, int b) {
  a = find(a), b = find(b);
  if (a != b) parent[b] = a;
}

vector<int> mst(int x, vector<pair<int, pair<int, int>>>& edges, int n, int m) {
  val = x;
  sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
    return abs(a.first - val) < abs(b.first - val);
  });
  parent = vector<int>(n); for (int i = 0; i < n; ++i) parent[i] = i;
  vector<int> weights(n - 1); int ind = 0;
  for (auto edge : edges) {
    int a = edge.second.first, b = edge.second.second;
    if (find(a) == find(b)) continue;
    weights[ind++] = edge.first;
    link(a, b);
  }
  return weights;
}

int main() {
  int n, m; cin >> n >> m;
  vector<pair<int, pair<int, int>>> edges(m);
  for (int i = 0; i < m; ++i) cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
  for (int i = 0; i < m; ++i) --edges[i].second.first, --edges[i].second.second;
  vector<int> t(m * (m - 1) / 2); int ind = 0;
  for (int i = 0; i < m; ++i) for (int j = i + 1; j < m; ++j) t[ind++] = (edges[i].first + edges[j].first + 2) / 2;
  sort(t.begin(), t.end());
  int p, k, a, b, c; cin >> p >> k >> a >> b >> c;
  vector<int> queries(k);
  for (int i = 0; i < p; ++i) cin >> queries[i];
  for (int i = p; i < k; ++i) queries[i] = (int) (((ll) queries[i - 1] * a + b) % c);
  sort(queries.begin(), queries.end());
  ind = -1;
  vector<int> MST;
  vector<ll> pMST;
  ll ans = 0;
  for (int i = 0; i < k; ++i) {
    int upper = upper_bound(t.begin(), t.end(), queries[i]) - t.begin();
    if (ind != upper) {
      ind = upper;
      MST = mst(queries[i], edges, n, m);
      sort(MST.begin(), MST.end());
      pMST = vector<ll>(n);
      for (int i = 0; i < n - 1; ++i) pMST[i + 1] = pMST[i] + MST[i];
    }
    upper = upper_bound(MST.begin(), MST.end(), queries[i]) - MST.begin();
    ans ^= (ll) queries[i] * upper - pMST[upper] + pMST[n - 1] - pMST[upper] - (ll) queries[i] * (n - 1 - upper);
  }
  cout << ans << '\n';
  return 0;
}
