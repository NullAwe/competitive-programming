#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n, m; cin >> n >> m;
  vector<int> eyes(n * m); for (int i = 0; i < n * m; ++i) cin >> eyes[i];
  vector<int> sorted = eyes;
  sort(sorted.begin(), sorted.end());
  map<int, int> indMap;
  indMap[sorted[0]] = 0;
  int val = 1;
  for (int i = 1; i < n * m; ++i)
    if (sorted[i] != sorted[i - 1]) indMap[sorted[i]] = val++;
  for (int i = 0; i < n * m; ++i) eyes[i] = indMap[eyes[i]];
  for (int i = 0; i < n * m; ++i) sorted[i] = indMap[sorted[i]];
  auto cmp = [&m](int a, int b) {
    if ((a / m) == (b / m)) return (a % m - b % m) < 0;
    return (a / m - b / m) > 0;
  };
  set<int, decltype(cmp)> s(cmp);
  vector<set<int, decltype(cmp)>> a(n * m, s);
  for (int i = 0; i < n * m; ++i) a[sorted[i]].insert(i);
  ll inc = 0;
  vector<vector<bool>> has(n, vector<bool>(m, false));
  for (int i = 0; i < n * m; ++i) {
    int spot = *a[eyes[i]].rbegin();
    a[eyes[i]].erase(spot);
    int x = spot / m, y = spot - spot / m * m;
    for (int j = 0; j < y; ++j) if (has[x][j]) ++inc;
    has[x][y] = true;
  }
  // Output:
  cout << inc << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}