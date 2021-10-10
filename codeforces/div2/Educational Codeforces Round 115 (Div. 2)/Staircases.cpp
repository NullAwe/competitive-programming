#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, m, q; cin >> n >> m >> q;
  vector<vector<int>> matr(n, vector<int>(m));
  ll has = 0;
  for (int j = n - 1; j >= 0; --j) {
    int x = j, y = 0, len = 0;
    while (x < n && y < m) {
      if (matr[x][y] == 0) ++len;
      else {
        has += (ll) len * (len - 1) / 2;
        len = 0;
      }
      if (x - j == y) ++x;
      else ++y;
    }
    has += (ll) len * (len - 1) / 2;
  }
  for (int i = 0; i < m; ++i) {
    int x = 0, y = i, len = 0;
    while (x < n && y < m) {
      if (matr[x][y] == 0) ++len;
      else {
        has += (ll) len * (len - 1) / 2;
        len = 0;
      }
      if (x == y - i) ++y;
      else ++x;
    }
    has += (ll) len * (len - 1) / 2;
  }
  has += n * m;
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b;
    int ha = a - 1, hb = b - 1, mi = min(a, b);
    a -= mi; b -= mi;
    vector<pair<int, int>> starts(2);
    if (a + b == 0) {
      starts[0] = {0, 0};
      starts[1] = {0, 0};
    } else if (a == 0) {
      starts[0] = {0, b};
      starts[1] = {0, b - 1};
    } else {
      starts[0] = {a - 1, 0};
      starts[1] = {a, 0};
    }
    for (int i = 0; i < 2; ++i) {
      bool flat = i;
      pair<int, int> p = starts[i];
      if (p.first == 0 && p.second > 0) flat = true;
      else if (p.second == 0 && p.first > 0) flat = false;
      int x = p.first, y = p.second, len = 0;
      if (flat) {
        while (x < n && y < m) {
          if (matr[x][y] == 0) ++len;
          else {
            has -= (ll) len * (len - 1) / 2;
            len = 0;
          }
          if (x == y - p.second) ++y;
          else ++x;
        }
        has -= (ll) len * (len - 1) / 2;
      } else {
        while (x < n && y < m) {
          if (matr[x][y] == 0) ++len;
          else {
            has -= (ll) len * (len - 1) / 2;
            len = 0;
          }
          if (x - p.first == y) ++x;
          else ++y;
        }
        has -= (ll) len * (len - 1) / 2;
      }
    }
    int tx = a, ty = b;
    while (tx < n && ty < m) {
      if (matr[tx][ty] == 0) --has;
      ++tx;
      ++ty;
    }
    matr[ha][hb] = 1 - matr[ha][hb];
    for (int i = 0; i < 2; ++i) {
      bool flat = i;
      pair<int, int> p = starts[i];
      if (p.first == 0 && p.second > 0) flat = true;
      else if (p.second == 0 && p.first > 0) flat = false;
      int x = p.first, y = p.second, len = 0;
      if (flat) {
        while (x < n && y < m) {
          if (matr[x][y] == 0) ++len;
          else {
            has += (ll) len * (len - 1) / 2;
            len = 0;
          }
          if (x == y - p.second) ++y;
          else ++x;
        }
        has += (ll) len * (len - 1) / 2;
      } else {
        while (x < n && y < m) {
          if (matr[x][y] == 0) ++len;
          else {
            has += (ll) len * (len - 1) / 2;
             len = 0;
          }
          if (x - p.first == y) ++x;
          else ++y;
        }
        has += (ll) len * (len - 1) / 2;
      }
    }
    tx = a, ty = b;
    while (tx < n && ty < m) {
      if (matr[tx][ty] == 0) ++has;
      ++tx;
      ++ty;
    }
    // Output:
    cout << has << endl;
  }
  return 0;
}
