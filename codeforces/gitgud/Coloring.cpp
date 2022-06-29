#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MOD = 998244353;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m, q; cin >> n >> m >> q;
  vector<vector<int>> rows(n, vector<int>(4)), cols(m, vector<int>(4));
  vector<int> cg(4);
  map<pii, int> vals;
  ll wr = 1, wc = 1;
  int zr = 0, zc = 0;
  for (int i = 0; i < n; ++i) wr = 2 * wr % MOD;
  for (int i = 0; i < m; ++i) wc = 2 * wc % MOD;
  for (int i = 0; i < q; ++i) {
    int a, b, t; cin >> a >> b >> t; --a, --b;
    int r = vals[{a, b}] - 1;
    if (r == t) {
      if (zr && zc) cout << 0 << '\n';
      else if (zr) cout << wc << '\n';
      else if (zc) cout << wr << '\n';
      else if (!cg[0] && !cg[1] && !cg[2] && !cg[3]) cout << (wr + wc + MOD - 2) % MOD << '\n';
      else if ((cg[0] | cg[3]) && (cg[1] | cg[2])) cout << (wr + wc) % MOD << '\n';
      else cout << (wr + wc + MOD - 1) % MOD << '\n';
      continue;
    }
    if (r >= 0) {
      if ((rows[a][0] | rows[a][3]) && (rows[a][1] | rows[a][2])) --zr;
      else if (!rows[a][0] && !rows[a][1] && !rows[a][2] && !rows[a][3]) wr = (MOD + 1) / 2 * wr % MOD;
      --rows[a][(r << 1) + (b & 1)];
      if ((rows[a][0] | rows[a][3]) && (rows[a][1] | rows[a][2])) ++zr;
      else if (!rows[a][0] && !rows[a][1] && !rows[a][2] && !rows[a][3]) wr = 2 * wr % MOD;
      if ((cols[b][0] | cols[b][3]) && (cols[b][1] | cols[b][2])) --zc;
      else if (!cols[b][0] && !cols[b][1] && !cols[b][2] && !cols[b][3]) wc = (MOD + 1) / 2 * wc % MOD;
      --cols[b][(r << 1) + (a & 1)];
      if ((cols[b][0] | cols[b][3]) && (cols[b][1] | cols[b][2])) ++zc;
      else if (!cols[b][0] && !cols[b][1] && !cols[b][2] && !cols[b][3]) wc = 2 * wc % MOD;
      --cg[(r << 1) + ((a + b) & 1)];
    }
    if (t >= 0) {
      if ((rows[a][0] | rows[a][3]) && (rows[a][1] | rows[a][2])) --zr;
      else if (!rows[a][0] && !rows[a][1] && !rows[a][2] && !rows[a][3]) wr = (MOD + 1) / 2 * wr % MOD;
      ++rows[a][(t << 1) + (b & 1)];
      if ((rows[a][0] | rows[a][3]) && (rows[a][1] | rows[a][2])) ++zr;
      else if (!rows[a][0] && !rows[a][1] && !rows[a][2] && !rows[a][3]) wr = 2 * wr % MOD;
      if ((cols[b][0] | cols[b][3]) && (cols[b][1] | cols[b][2])) --zc;
      else if (!cols[b][0] && !cols[b][1] && !cols[b][2] && !cols[b][3]) wc = (MOD + 1) / 2 * wc % MOD;
      ++cols[b][(t << 1) + (a & 1)];
      if ((cols[b][0] | cols[b][3]) && (cols[b][1] | cols[b][2])) ++zc;
      else if (!cols[b][0] && !cols[b][1] && !cols[b][2] && !cols[b][3]) wc = 2 * wc % MOD;
      ++cg[(t << 1) + ((a + b) & 1)];
    }
    vals[{a, b}] = t + 1;
    if (zr && zc) cout << 0 << '\n';
    else if (zr) cout << wc << '\n';
    else if (zc) cout << wr << '\n';
    else if (!cg[0] && !cg[1] && !cg[2] && !cg[3]) cout << (wr + wc + MOD - 2) % MOD << '\n';
    else if ((cg[0] | cg[3]) && (cg[1] | cg[2])) cout << (wr + wc) % MOD << '\n';
    else cout << (wr + wc + MOD - 1) % MOD << '\n';
  }
  return 0;
}

