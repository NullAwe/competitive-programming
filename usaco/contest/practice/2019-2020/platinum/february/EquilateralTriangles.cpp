#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> arr;
vector<vector<int>> ud, du;

inline bool has(int i, int j) { return (i < 0 || j < 0 || i >= n || j >= n) ? false : arr[i][j] == '*'; }

inline int qry(int i1, int j1, int i2, int j2) {
  if (i1 + j1 == i2 + j2) {
    int ind = i1 + j1, ind2 = min(n - 1 - i1, j1), ind3 = min(n - 1 - i2, j2);
    int a = min(ind2, ind3), b = max(ind2, ind3);
    if (ind < 0 || ind >= 2 * n || b < 0 || a >= n) return 0;
    return du[ind][min(b, n - 1) + 1] - du[ind][max(a, 0)];
  }
  if (i1 >= j1 && i1 - j1 >= n) return 0;
  int ind = (i1 >= j1 ? i1 - j1 : j1 - i1 + n), ind2 = min(i1, j1), ind3 = min(i2, j2);
  int a = min(ind2, ind3), b = max(ind2, ind3);
  if (ind < 0 || ind >= 2 * n || b < 0 || a >= n) return 0;
  return ud[ind][min(b, n - 1) + 1] - ud[ind][max(a, 0)];
}

int main() {
  ifstream in("triangles.in");
  ofstream out("triangles.out");
  in >> n;
  arr.resize(n); for (int i = 0; i < n; ++i) in >> arr[i];
  ud = du = vector<vector<int>>(2 * n, vector<int>(n + 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int ind = (i >= j ? i - j : j - i + n), ind2 = min(i, j);
      ud[ind][ind2 + 1] = ud[ind][ind2] + has(i, j);
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < n; ++j) {
      int ind = i + j, ind2 = min(n - 1 - i, j);
      du[ind][ind2 + 1] = du[ind][ind2] + has(i, j);
    }
  }
  for (int i = 0; i < 2 * n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (ud[i][j] < ud[i][j - 1]) ud[i][j] = ud[i][j - 1];
      if (du[i][j] < du[i][j - 1]) du[i][j] = du[i][j - 1];
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (!has(i, j)) continue;
      for (int k = 2; k < 2 * n; k += 2) {
        for (int s1 = -1; s1 < 2; s1 += 2) for (int s2 = -1; s2 < 2; s2 += 2) {
          if (!has(i + s1 * k / 2, j + s2 * k / 2)) continue;
          ans += qry(i - s1 * k / 2, j + s2 * k / 2, i - s1, j + s2 * (k - 1));
          ans += qry(i + s1 * k / 2, j - s2 * k / 2, i + s1 * (k - 1), j - s2);
        }
      }
    }
  }
  out << ans / 2 << '\n';
  return 0;
}
