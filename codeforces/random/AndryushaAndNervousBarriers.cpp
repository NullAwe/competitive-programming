#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define ll long long

const int MOD = 1e9 + 7;

vector<int> t;
int n;

void build() {
  t.resize(2 * n);
  for (int i = 1; i < 2 * n; ++i) t[i] = -1;
}

void modify(int p, int v) { for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]); }

int query(int l, int r) {
  int ans = -1;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = max(ans, t[l++]);
    if (r & 1) ans = max(ans, t[--r]);
  }
  return ans;
}

int main() {
  int h, w; cin >> h >> w >> n;
  vector<vector<int>> b(n, vector<int>(4));
  for (int i = 0; i < n; ++i) for (int j = 0; j < 4; ++j) cin >> b[i][j];
  sort(b.begin(), b.end()), reverse(b.begin(), b.end());
  for (int i = 0; i < n; ++i) for (int j = 0; j < 3; ++j) --b[i][j];
  vector<vector<int>> come(w), go(w);
  for (int i = 0; i < n; ++i) come[b[i][1]].push_back(i), go[b[i][2]].push_back(i);
  vector<vector<int>> qs(w); for (int i = 0; i < w; ++i) qs[i].push_back(-1);
  for (int i = 0; i < n; ++i) {
    if (b[i][1]) qs[b[i][1] - 1].push_back(i);
    if (b[i][2] < w - 1) qs[b[i][2] + 1].push_back(i);
  }
  build();
  map<pii, int> qa;
  for (int i = 0; i < w; ++i) {
    for (int ind : come[i]) modify(ind, b[ind][0] + b[ind][3]);
    for (int ind : qs[i]) {
      int lo = ind, hi = n;
      while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if ((ind < 0 ? h : b[ind][0]) > query(ind + 1, mid + 1)) lo = mid;
        else hi = mid;
      }
      qa[{i, ind}] = hi;
    }
    for (int ind : go[i]) modify(ind, -1);
  }
  vector<int> dp(n + 1); for (int i = 0; i < w; ++i) ++dp[qa[{i, -1}]];
  for (int i = 0; i < n; ++i) {
    int l = b[i][1] ? b[i][1] - 1 : b[i][2] + 1, r = b[i][2] < w - 1 ? b[i][2] + 1 : b[i][1] - 1;
    int nl = qa[{l, i}], nr = qa[{r, i}];
    dp[nl] = (dp[nl] + dp[i]) % MOD, dp[nr] = (dp[nr] + dp[i]) % MOD;
  }
  cout << dp[n] << '\n';
  return 0;
}

