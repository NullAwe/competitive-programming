#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<vector<int>> w;
vector<ll> vals;
vector<int> r, p;

int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

void link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return;
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
}

int main() {
  int n, m; cin >> n >> m;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  set<int> nums; for (int num : arr) nums.insert(num);
  vector<int> copy(nums.begin(), nums.end());
  vector<vector<pii>> edges(copy.size());
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    edges[lower_bound(copy.begin(), copy.end(), max(arr[a], arr[b])) - copy.begin()].push_back({a, b});
  }
  w.resize(n), vals.resize(n), r.resize(n), p.resize(n);
  for (int i = 0; i < n; ++i) w[i].push_back(i), vals[i] = arr[i], p[i] = i;
  for (int i = 0; i < copy.size(); ++i) {
    for (pii edge : edges[i]) {
      int a = edge.first, b = edge.second;
      int pa = find(a), pb = find(b);
      if (pa == pb) continue;
      link(a, b);
      int np = find(a);
      if (vals[pa] < arr[b]) swap(w[np], w[pb]);
      else if (vals[pb] < arr[a]) swap(w[np], w[pa]);
      else {
        if (w[pa].size() < w[pb].size()) swap(w[pa], w[pb]);
        for (int v : w[pb]) w[pa].push_back(v);
        swap(w[np], w[pa]);
      }
      vals[np] = vals[pa] + vals[pb];
    }
  }
  vector<bool> ans(n);
  for (int v : w[find(0)]) ans[v] = true;
  for (int num : ans) cout << num;
  cout << '\n';
  return 0;
}
