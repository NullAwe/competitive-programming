#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

int main() {
  int n, m; cin >> n >> m;
  vector<pair<pii, ll>> edges(m);
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    edges[i] = {{a, b}, w};
  }
  vector<ll> d(n);
  vector<int> from(n);
  int last;
  for (int i = 0; i < n; ++i) {
    last = -1;
    for (pair<pii, ll> p : edges) {
      if (d[p.first.second] <= d[p.first.first] + p.second) continue;
      d[p.first.second] = d[p.first.first] + p.second;
      from[p.first.second] = p.first.first;
      last = p.first.second;
    }
  }
  if (last < 0) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  for (int i = 0; i < n; ++i) last = from[last];
  vector<int> ans;
  for (int node = last; node != last || ans.size() < 2; node = from[node]) ans.push_back(node);
  ans.push_back(last);
  for (int i = ans.size() - 1; i >= 0; --i) cout << ans[i] + 1 << ' ';
  cout << '\n';
  return 0;
}

