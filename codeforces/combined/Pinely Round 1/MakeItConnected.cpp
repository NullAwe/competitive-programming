#include <bits/stdc++.h>
using namespace std;

vector<int> r, p;
vector<string> arr;
vector<bool> vis;
vector<int> cnts;

int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

void link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return;
  if (r[a] < r[b]) swap(a, b);
  r[a] += r[b], p[b] = a;
}

int dfs(int v) {
  if (vis[v]) return -1;
  vis[v] = true;
  vector<int> later;
  for (int i = 0; i < arr[v].size(); ++i) {
    if (arr[v][i] == '1' && cnts[i] == r[find(i)] - 1) {
      int val = dfs(i);
      if (val != -1) return val;
    } else if (arr[v][i] == '1') later.push_back(i);
  }
  for (int u : later) {
    int val = dfs(u);
    if (val != -1) return val;
  }
  if (cnts[v] == r[find(v)] - 1) return -1;
  return v;
}

void solve() {
  int n; cin >> n;
  r.resize(n), p.resize(n);
  for (int i = 0; i < n; ++i) r[i] = 1, p[i] = i;
  arr.resize(n), cnts.resize(n), cnts.assign(n, 0);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
    if (arr[i][j] == '1') link(i, j), ++cnts[i];
  if (r[find(0)] == n) {
    cout << "0\n";
    return;
  }
  int mn = INT_MAX, v = -1;
  set<int> ps;
  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < n; ++j) cnt += arr[i][j] - '0';
    if (cnt != r[find(i)] - 1) {
      vis = vector<bool>(n);
      cout << "1\n" << dfs(i) + 1 << '\n';
      return;
    }
    if (r[find(i)] < mn) mn = r[find(i)], v = find(i);
    ps.insert(find(i));
  }
  if (ps.size() > 2 && mn > 1) {
    cout << 2 << '\n' << 1 << ' ';
    for (int i = 0; i < n; ++i) {
      if (find(i) != find(0)) {
        cout << i + 1 << '\n';
        return;
      }
    }
  }
  cout << mn << '\n';
  for (int i = 0; i < n; ++i) if (find(i) == v && i != v) cout << i + 1 << ' ';
  cout << v + 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
