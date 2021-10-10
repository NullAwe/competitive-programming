#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n, m; cin >> n >> m;
    vector<int> styles(m);
    for (int j = 0; j < m; ++j) cin >> styles[j];
    sort(styles.begin(), styles.end());
    map<int, vector<int>> sm;
    for (int j = 0; j < m; ++j) sm[styles[j]].push_back(j);
    vector<bool> used(m, false);
    int change = 0;
    for (int j = 0; j < n; ++j) {
      vector<int> order(m);
      for (int k = 0; k < m; ++k) cin >> order[k];
      sort(order.begin(), order.end());
      vector<int> toChange;
      int i1 = 0, i2 = 0;
      while (i1 < m && i2 < m) {
        if (styles[i1] == order[i2]) {
          ++i1; ++i2;
        } else if (styles[i1] < order[i2]) {
          toChange.push_back(styles[i1]);
          ++i1;
        } else ++i2;
      }
      while (i1 < m) toChange.push_back(styles[i1++]);
      change += toChange.size();
      for (int ch : toChange) {
        if (!sm[ch].empty()) {
          --change;
          used[sm[ch][sm[ch].size() - 1]] = true;
          sm[ch].resize(sm[ch].size() - 1);
        }
      }
      styles = order;
    }
    // Output:
    cout << "Case #" << i << ": ";
    cout << change;
    cout << endl;
  }
  return 0;
}
