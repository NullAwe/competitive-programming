#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<vector<int>> sets(n);
  map<int, int> compress;
  int val = 0;
  for (int i = 0; i < n; ++i) {
    int m; cin >> m;
    sets[i].resize(m);
    for (int j = 0; j < m; ++j) {
      int a; cin >> a;
      // Performs compression:
      if (!compress.count(a)) compress[a] = val++;
      sets[i][j] = compress[a];
    }
    sort(sets[i].begin(), sets[i].end());
  }
  vector<vector<int>> back(val);
  for (int i = 0; i < n; ++i)
    for (int num : sets[i]) back[num].push_back(i);
  // Checks the larger sets:
  for (int i = 0; i < n; ++i) {
    if (sets[i].size() < 448) continue;
    vector<bool> has(n, false);
    for (int num : sets[i]) {
      for (int thisNum : back[num]) {
        if (thisNum == i) continue;
        if (has[thisNum]) {
          // Output:
          cout << thisNum + 1 << " " << i + 1 << endl;
          return;
        }
        has[thisNum] = true;
      }
    }
  }
  // Checks the smaller sets:
  vector<int> xs(val, -1), inds(val, -1);
  for (int i = 0; i < val; ++i) {
    for (int num : back[i]) {
      if (sets[num].size() > 447) continue;
      for (int j = 0; sets[num][j] < i; ++j) {
        if (xs[sets[num][j]] == i) {
          // Output:
          cout << inds[sets[num][j]] + 1 << " " << num + 1 << endl;
          return;
        }
        xs[sets[num][j]] = i;
        inds[sets[num][j]] = num;
      }
    }
  }
  // Output:
  cout << -1 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
