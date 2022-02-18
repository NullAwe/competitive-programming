#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q, sz = 30; cin >> n >> q;
  int up[n][sz];
  for (int i = 0; i < n; ++i) cin >> up[i][0];
  for (int i = 0; i < n; ++i) --up[i][0];
  for (int j = 1; j < sz; ++j) for (int i = 0; i < n; ++i) up[i][j] = up[up[i][j - 1]][j - 1];
  for (int i = 0; i < q; ++i) {
    int x, k; cin >> x >> k; --x;
    for (int ind = 0; ind < sz; ++ind) if (k & (1 << ind)) x = up[x][ind];
    // Output:
    cout << x + 1 << endl;
  }
  return 0;
}
