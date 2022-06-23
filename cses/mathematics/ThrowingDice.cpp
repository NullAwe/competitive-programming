#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

struct M {

  vector<vector<ll>> m;

  M() : m(6, vector<ll>(6)) {}

  M operator*(M other) {
    vector<vector<ll>> om = other.m;
    M prod;
    for (int row = 0; row < 6; ++row) for (int col = 0; col < 6; ++col)
      for (int i = 0; i < 6; ++i) prod.m[row][col] = (prod.m[row][col] + m[i][col] * om[row][i]) % MOD;
    return prod;
  }
};

M identity() {
  M id;
  for (int i = 0; i < 6; ++i) id.m[i][i] = 1;
  return id;
}

M base() {
  M b;
  for (int i = 0; i < 5; ++i) b.m[i][i + 1] = b.m[5][i] = b.m[5][i + 1] = 1;
  return b;
}

M p(ll y) {
  if (!y) return identity();
  M b = p(y >> 1);
  b = b * b;
  if (y & 1) b = b * base();
  return b;
}

int main() {
  ll n; cin >> n;
  cout << p(n).m[5][5] << '\n';
  return 0;
}

