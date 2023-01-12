#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct DSU {
  
  vector<int> r, p;
  vector<int> sz, esz;

  DSU(int n) : r(n), p(n), sz(n, 1), esz(n) {
    for (int i = 0; i < n; ++i) p[i] = i;
  }

  int find(int a) {
    return a == p[a] ? a : p[a] = find(p[a]);
  }

  void link(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) {
      ++esz[a];
      return;
    }
    if (r[a] < r[b]) swap(r[a], r[b]);
    if (r[a] == r[b]) ++r[a];
    p[b] = a, sz[a] += sz[b], esz[a] += esz[b] + 1;
  }
};

const int MOD = 998244353;

ll p2(ll y) {
  if (y < 0) return 0;
  if (!y) return 1;
  ll b = p2(y >> 1);
  b = b * b % MOD;
  if (y & 1) b *= 2;
  return b % MOD;
}

int main() {
  int n, m; cin >> n >> m;
  bool sw = m % 2 == 0;
  if (sw) swap(n, m);
  vector<vector<char>> arr(n, vector<char>(m));
  if (sw) swap(n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (sw) cin >> arr[j][i];
      else cin >> arr[i][j];
    }
  }
  if (sw) swap(n, m);
  if (m % 2 == 0) {
    int q = 0;
    for (vector<char> vc : arr) for (char ch : vc) if (ch == '?') ++q;
    cout << p2(q) << '\n';
  } else if (n % 2 == 0) {
    vector<ll> ws(2, 1);
    for (vector<char> vc : arr) {
      int q = 0, o = 0;
      for (char ch : vc) {
        if (ch == '?') ++q;
        else if (ch == '1') ++o;
      }
      if (!q) ws[1 - (o & 1)] = 0;
      else {
        ws[0] = ws[0] * p2(q - 1) % MOD;
        ws[1] = ws[1] * p2(q - 1) % MOD;
      }
    }
    cout << (ws[0] + ws[1]) % MOD << '\n';
  } else {
    vector<int> rs(n), cs(m);
    DSU dsu(n + m);
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
      int val = arr[i][j] - '0';
      if (arr[i][j] == '?') dsu.link(i, j + n), val = 0;
      rs[i] ^= val, cs[j] ^= val;
    }
    vector<vector<int>> track(n + m);
    for (int i = 0; i < n + m; ++i) track[dsu.find(i)].push_back(i);
    vector<ll> ws(2, 1);
    vector<bool> done(n + m);
    for (int i = 0; i < n + m; ++i) {
      int v = dsu.find(i);
      if (done[v]) continue;
      done[v] = true;
      int x = 0;
      for (int num : track[v]) {
        if (num < n) x ^= rs[num];
        else x ^= cs[num - n];
      }
      int sz = dsu.sz[v], esz = dsu.esz[v];
      if (sz % 2 == 0) {
        if (x % 2 == 0) {
          ws[0] = ws[0] * p2(esz - (sz - 1)) % MOD;
          ws[1] = ws[1] * p2(esz - (sz - 1)) % MOD;
        } else {
          ws[0] = ws[1] = 0;
        }
      } else {
        if (x % 2 == sz % 2) {
          ws[0] = ws[0] * p2(esz - (sz - 1)) % MOD;
          ws[1] = 0;
        } else {
          ws[0] = 0;
          ws[1] = ws[1] * p2(esz - (sz - 1)) % MOD;
        }
      }
    }
    cout << (ws[0] + ws[1]) % MOD << '\n';
  }
  return 0;
}
