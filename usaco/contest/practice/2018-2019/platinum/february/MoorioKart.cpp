#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define cd complex<double>

typedef unsigned long long ull;
typedef __uint128_t L;

const int MOD = 1e9 + 7;
const double PI = acos(-1);

struct FastMod {

  ull b, m;

  FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}

  ull reduce(ull a) {
    ull q = (ull) ((L(m) * a) >> 64), r = a - q * b;
    return r >= b ? r - b : r;
  }
};

inline ll add(ll x, ll y) {
  ll ans = x + y;
  return ans >= MOD ? ans - MOD : ans;
}

inline ll sub(ll x, ll y) {
  ll ans = x - y;
  return ans < 0 ? ans + MOD : ans;
}

FastMod F(MOD);

vector<int> r, p;

inline int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

inline void link(int a, int b) {
  a = find(a), b = find(b);
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
}

int n, m, x, y, k = 0;
vector<int> roots, inds;
vector<vector<vector<pii>>> adjs;

vector<vector<ll>> lens;
vector<ll> yp, na;
vector<ll> glens(1, 1);
ll gyp = 0, gna = 0;

inline vector<ll> dfs(int v, int p, int ind) {
  vector<vector<ll>> cs;
  for (pii u : adjs[ind][v]) {
    int node = u.first, len = u.second;
    if (node == p) continue;
    vector<ll> next = dfs(node, v, ind);
    for (int i = 0; i < next.size(); ++i) next[i] += len;
    cs.push_back(next);
  }
  vector<ll> itself(1);
  cs.push_back(itself);
  int len = cs.size();
  if (len == 1) return itself;
  int all = 0;
  for (int i = 0; i < len; ++i) {
    for (int len1 : cs[i]) {
      ++all;
      for (int j = i + 1; j < len; ++j) {
        for (int len2 : cs[j]) {
          int tlen = len1 + len2;
          if (tlen <= y) ++lens[ind][tlen];
          else yp[ind] = add(yp[ind], tlen), ++na[ind];
        }
      }
    }
  }
  vector<ll> ans(all); int j = 0;
  for (int i = 0; i < len; ++i) for (int len1 : cs[i]) ans[j++] = len1;
  return ans;
}

inline void add(int ind) {
  ll tn = na[ind];
  for (int i = 0; i < lens[ind].size(); ++i) tn += lens[ind][i];
  ll ngyp = F.reduce(gyp * na[ind] + yp[ind] * gna), ngna = F.reduce(gna * na[ind]);
  ll sum = 0, sum2 = 0;
  for (int i = 0; i < glens.size(); ++i) sum = add(sum, F.reduce(i * glens[i])), sum2 = add(sum2, glens[i]);
  ngyp = add(ngyp, F.reduce(sum * na[ind] + yp[ind] * sum2)), ngna = add(ngna, F.reduce(sum2 * na[ind]));
  ll sum3 = 0, sum4 = 0;
  for (int i = 0; i < lens[ind].size(); ++i) sum3 = add(sum3, F.reduce(i * lens[ind][i])), sum4 = add(sum4, lens[ind][i]);
  ngyp = add(ngyp, F.reduce(gyp * sum4 + sum3 * gna)), ngna = add(ngna, F.reduce(gna * sum4));
  vector<ll> after(glens.size() + lens[ind].size());
  for (int i = 0; i < lens[ind].size(); ++i) {
    if (!lens[ind][i]) continue;
    for (int j = 0; j < glens.size(); ++j) after[i + j] = add(after[i + j], F.reduce(glens[j] * lens[ind][i]));
  }
  for (int i = y + 1; i < after.size(); ++i) ngyp = add(ngyp, F.reduce(i * after[i])), ngna = add(ngna, after[i]);
  for (int i = 0; i < after.size(); ++i) after[i] = F.reduce(after[i]);
  after.resize(y + 1);
  glens = after, gyp = ngyp, gna = ngna;
}

int main() {
  ifstream in("mooriokart.in");
  ofstream out("mooriokart.out");
  in >> n >> m >> x >> y;
  vector<pair<pii, int>> edges(m);
  r.resize(n), p.resize(n);
  for (int i = 0; i < n; ++i) p[i] = i;
  for (int i = 0; i < m; ++i) {
    int a, b, c; in >> a >> b >> c; --a, --b;
    edges[i] = {{a, b}, c};
    link(a, b);
  }
  inds = vector<int>(n, -1);
  for (int i = 0; i < n; ++i) {
    int p = find(i);
    if (inds[p] >= 0) continue;
    inds[p] = k++, roots.push_back(p);
  }
  adjs.resize(k);
  vector<int> maps(n, -1), at(k, 0);
  for (pair<pii, int> e : edges) {
    int a = e.first.first, b = e.first.second, c = e.second, i = inds[find(a)];
    if (maps[a] < 0) maps[a] = at[i]++;
    if (maps[b] < 0) maps[b] = at[i]++;
  }
  for (int i = 0; i < k; ++i) adjs[i].resize(max(at[i], 1));
  for (pair<pii, int> e : edges) {
    int a = e.first.first, b = e.first.second, c = e.second, i = inds[find(a)];
    adjs[i][maps[a]].push_back({maps[b], c});
    adjs[i][maps[b]].push_back({maps[a], c});
  }
  y -= min(k * x, y);
  lens = vector<vector<ll>>(k, vector<ll>(y + 1)), yp.resize(k), na.resize(k);
  for (int i = 0; i < k; ++i) dfs(0, 0, i), add(i);
  if (glens.size() > y) gyp = F.reduce(gyp + glens[y] * y), gna = add(gna, glens[y]);
  gyp = add(gyp, F.reduce(F.reduce(k * x) * gna));
  for (int i = 0; i < k - 1; ++i) gyp = add(gyp, gyp);
  for (int i = 2; i < k; ++i) gyp = F.reduce(gyp * i);
  out << gyp << '\n';
  return 0;
}
