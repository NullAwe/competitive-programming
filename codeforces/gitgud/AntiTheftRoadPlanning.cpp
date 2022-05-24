#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> d(32);
  for (int i = 1; i < 32; ++i) {
    int ms = 1, temp = i;
    while (temp > 1) ms <<= 1, temp >>= 1;
    if (ms == i) d[i] = ms * ms;
    else d[i] = d[ms * 2 - i];
  }
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < n; ++j) cout << d[j] << ' ';
    cout << '\n';
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < n; ++j) cout << 2 * d[i] << ' ';
    cout << '\n';
  }
  fflush(stdout);
  int x = 0, y = 0;
  for (int i = 0; i < q; ++i) {
    int s; scanf("%d", &s);
    vector<vector<int>> dist(n, vector<int>(n));
    for (int j = x - 1; j >= 0; --j) dist[j][y] = dist[j + 1][y] ^ (2 * d[j + 1]);
    for (int j = x + 1; j < n; ++j) dist[j][y] = dist[j - 1][y] ^ (2 * d[j]);
    for (int j = y - 1; j >= 0; --j) for (int k = 0; k < n; ++k) dist[k][j] = dist[k][j + 1] ^ d[j + 1];
    for (int j = y + 1; j < n; ++j) for (int k = 0; k < n; ++k) dist[k][j] = dist[k][j - 1] ^ d[j];
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        if (dist[j][k] == s) {
          x = j, y = k;
          break;
        }
      }
    }
    printf("%d %d\n", x + 1, y + 1);
    fflush(stdout);
  }
  return 0;
}
