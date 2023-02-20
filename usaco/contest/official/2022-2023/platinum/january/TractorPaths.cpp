#include <bits/stdc++.h>
using namespace std;

const int SZ = 18;
const int LOG = 8;
const int SQRT = 256;

int n;
string sp;
vector<vector<int>> up, down;
vector<int> pref;
vector<vector<int>> sqrtUp, sqrtDown;

inline int jmp(int a, int u) {
  for (int i = 0; i < SZ; ++i) if (u & (1 << i)) a = up[i][a];
  return a;
}

inline int jmp2(int a, int u) {
  for (int i = 0; i < SZ; ++i) if (u & (1 << i)) a = down[i][a];
  return a;
}

inline int dist(int l, int r) {
  int u = 0;
  for (int i = SZ - 1; i >= 0; --i) if (up[i][l] < r) l = up[i][l], u += (1 << i);
  return u + (l < r);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int q; cin >> n >> q;
  string str; cin >> str;
  vector<int> until(n);
  int cl = 0, cr = 0;
  for (int i = 0; i < 2 * n; ++i) {
    if (str[i] == 'L') ++cl;
    else until[cr++] = cl - 1; // inclusive, cl for exclusive
  }
  vector<int> bck(n);
  cl = cr = 0;
  for (int i = 2 * n - 1; i >= 0; --i) {
    if (str[i] == 'R') ++cr;
    else bck[n - (++cl)] = n - cr; // inclusive, cr for exclusive
  }
  up = vector<vector<int>>(SZ, vector<int>(n));
  for (int i = 0; i < n; ++i) up[0][i] = until[i];
  for (int i = 1; i < SZ; ++i) for (int j = 0; j < n; ++j)
    up[i][j] = up[i - 1][up[i - 1][j]];
  down = vector<vector<int>>(SZ, vector<int>(n));
  for (int i = 0; i < n; ++i) down[0][i] = bck[i];
  for (int i = 1; i < SZ; ++i) for (int j = 0; j < n; ++j)
    down[i][j] = down[i - 1][down[i - 1][j]];
  cin >> sp;
  pref.resize(n + 1); for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + sp[i] - '0';
  sqrtUp = vector<vector<int>>(n, vector<int>(SQRT + 1));
  sqrtDown = vector<vector<int>>(n, vector<int>(SQRT + 1));
  for (int i = 0; i < n; ++i) {
    int at = i;
    for (int j = 0; j < SQRT; ++j) {
      at = up[0][at];
      sqrtUp[i][j + 1] = sqrtUp[i][j] + pref[at + 1];
    }
  }
  for (int i = 0; i < n; ++i) {
    int at = i;
    for (int j = 0; j < SQRT; ++j) {
      at = down[0][at];
      sqrtDown[i][j + 1] = sqrtDown[i][j] + pref[at];
    }
  }
  for (int i = 0; i < q; ++i) {
    int l, r; cin >> l >> r; --l, --r;
    int ans = dist(l, r);
    int tl = l;
    int sum = sp[l] + sp[r] - 2 * '0';
    int td = ans - 1;
    while (td > 0) {
      int add = min(td, SQRT);
      sum += sqrtUp[tl][add];
      if (add == SQRT) tl = up[LOG][tl];
      else tl = jmp(tl, add);
      td -= add;
    }
    int tr = r;
    td = ans - 1;
    while (td > 0) {
      int add = min(td, SQRT);
      sum -= sqrtDown[tr][add];
      if (add == SQRT) tr = down[LOG][tr];
      else tr = jmp2(tr, add);
      td -= add;
    }
    cout << ans << ' ' << sum << '\n';
  }
  return 0;
}
