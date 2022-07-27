#include <bits/stdc++.h>
using namespace std;

#define ll long long

const vector<int> nt = {3, 5, 8, 13, 21, 34, 55}, ot = {1, 2, 3, 5, 8, 13, 21}, tt = {0, 1, 1, 2, 3, 5, 8}, p2 = {1, 2, 4, 8, 16, 32, 64}, add = {0};
const int MOD = 1e9 + 7;

struct Matrix {

  int n, m;
  vector<vector<int>> matrix;

  Matrix() : n(0), m(0), matrix(0) {}

  Matrix(vector<vector<int>>& arr) : n(arr.size()), m(arr[0].size()), matrix(arr.begin(), arr.end()) {}

  Matrix operator*(Matrix& other) {
    vector<vector<int>> prod(matrix.size(), vector<int>(other.matrix[0].size()));
    for (int i = 0; i < matrix.size(); ++i)
      for (int j = 0; j < other.matrix[0].size(); ++j)
        for (int k = 0; k < matrix[i].size(); ++k)
          prod[i][j] = (prod[i][j] + (long long) matrix[i][k] * other.matrix[k][j]) % MOD;
    return Matrix(prod);
  }
};

Matrix id[8], bs[8];

Matrix p(int i, int y) {
  if (!y) return id[i];
  Matrix b = p(i, y >> 1);
  return (b * b) * (y & 1 ? bs[i] : id[i]);
}

inline int trans(int a, int sz) {
  vector<bool> bits(sz); for (int i = 0; i < sz; ++i) bits[i] = a & (1 << i);
  int beg = 0, ans = 1;
  for (int i = 1; i < sz; ++i) {
    if (bits[i] != bits[beg])
      ans *= bits[beg] ? (!beg ? ot[i - beg - 1] : nt[i - beg - 1]) : p2[i - beg - 1], beg = i;
  }
  return ans * (bits[beg] ? (!beg ? tt[sz - beg - 1] : ot[sz - beg - 1]) : p2[sz - beg - 1]);
}

int main() {
  for (int sz = 1; sz < 8; ++sz) {
    vector<vector<int>> a(1 << sz, vector<int>(1 << sz)), b(1 << sz, vector<int>(1 << sz));
    for (int i = 0; i < (1 << sz); ++i) {
      a[i][i] = 1;
      for (int j = 0; j < (1 << sz); ++j) b[i][j] = trans(i & j, sz);
    }
    id[sz] = Matrix(a), bs[sz] = Matrix(b);
  }
  vector<int> arr(8); for (int i = 1; i < 8; ++i) cin >> arr[i];
  int last = 7; while (!arr[last]) --last;
  vector<vector<int>> cur(1, vector<int>(1, 1));
  for (int i = 1; i < 8; ++i) {
    reverse(cur.begin(), cur.end());
    while (cur.size() < (1 << i)) cur.push_back(add);
    reverse(cur.begin(), cur.end());
    Matrix mult = p(i, i == last ? arr[i] - 1 : arr[i]), curM = Matrix(cur);
    cur = (mult * curM).matrix;
  }
  int ans = 0;
  for (int i = 0; i < cur.size(); ++i) ans = (ans + (long long) cur[i][0] * trans(i, last)) % MOD;
  cout << ans << '\n';
  return 0;
}

