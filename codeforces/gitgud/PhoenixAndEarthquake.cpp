#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<int> r, p;

int find(int a) {
  return a == p[a] ? a : p[a] = find(p[a]);
}

void link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return;
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
}

int main() {
  int n, m, x; cin >> n >> m >> x;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<pii>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back({b, i}), adj[b].push_back({a, i});
  }
  r.resize(n), p.resize(n); for (int i = 0; i < n; ++i) p[i] = i;
  vector<set<pair<ll, pii>>> np(n);
  vector<set<pair<ll, pii>>*> sets(n);
  for (int i = 0; i < n; ++i) {
    for (pii v : adj[i]) np[i].insert({arr[find(v.first)], v});
    sets[i] = &np[i];
  }
  vector<int> order;
  for (int i = 0; i < n; ++i) {
    if (find(i) != i) continue;
    sets[i]->clear(); for (pii v : adj[i]) sets[i]->insert({arr[find(v.first)], v});
    ll cur = arr[i];
    while (sets[i]->size()) {
      pair<ll, pii> big = *--sets[i]->end();
      int v = big.second.first, vp = find(v);
      if (arr[vp] + cur < x) break;
      sets[i]->erase(big);
      if (find(i) == vp) continue;
      order.push_back(big.second.second);
      if (sets[i]->size() < sets[vp]->size()) swap(sets[i], sets[vp]);
      for (auto val : *sets[vp]) sets[i]->insert({arr[find(val.second.first)], val.second});
      link(i, v);
      sets[find(i)] = sets[i], cur = arr[find(i)] = arr[vp] + cur - x;
    }
  }
  if (order.size() != n - 1) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  for (int num : order) cout << num + 1 << '\n';
  return 0;
}
