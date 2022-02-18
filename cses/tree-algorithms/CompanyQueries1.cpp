#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, q; cin >> n >> q;
  vector<int> parents(n);
  for (int i = 1; i < n; ++i) cin >> parents[i];
  for (int i = 0; i < n; ++i) --parents[i];
  int sz = 1;
  for (int i = 1; i < n; i <<= 1) ++sz;
  vector<vector<int>> up(n, vector<int>(sz));
  for (int i = 0; i < n; ++i) up[i][0] = parents[i];
  for (int j = 1; j < sz; ++j) for (int i = 0; i < n; ++i)
    up[i][j] = (up[i][j - 1] >= 0 ? up[up[i][j - 1]][j - 1] : -1);
  for (int i = 0; i < q; ++i) {
    int node, boss; cin >> node >> boss; --node;
    while (boss > 0) {
      int j, ind = 0;
      for (j = 1; (j << 1) <= boss; j <<= 1) ++ind;
      if (ind >= sz || up[node][ind] < 0) {
        // Output:
        cout << -1 << endl;
        break;
      }
      boss -= j;
      node = up[node][ind];
    }
    // Output:
    if (!boss) cout << node + 1 << endl;
  }
  return 0;
}
