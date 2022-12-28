#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> r, p;
vector<bool> closed;

int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

void link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) {
    closed[a] = true;
    return;
  }
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
  if (closed[a] || closed[b]) closed[a] = closed[b] = true;
}

int main() {
  int n, m; cin >> n >> m;
  r.resize(n), p.resize(n), closed.resize(n);
  for (int i = 0; i < n; ++i) p[i] = i;
  vector<pair<int, pii>> arr(m);
  for (int i = 0; i < m; ++i) cin >> arr[i].second.first >> arr[i].second.second >> arr[i].first;
  sort(arr.begin(), arr.end()), reverse(arr.begin(), arr.end());
  int ans = 0;
  for (pair<int, pii> p : arr) {
    int a = find(p.second.first - 1), b = find(p.second.second - 1);
    if (closed[a] && closed[b]) continue;
    ans += p.first;
    link(a, b);
  }
  cout << ans << '\n';
  return 0;
}
