#include <bits/stdc++.h>
using namespace std;

#define ll __int128
#define pii pair<int, int>

const int MOD = 1e9 + 7;
const int MAX_N = 50001;
const int MAX_Q = 200001;

int k, arr[MAX_N], ans[MAX_Q];
vector<pii> qs[MAX_N];
vector<vector<vector<int>>> pre;
vector<vector<int>> diff;

inline void init() {
  diff.resize(k);
  for (int i = 0; i < k; ++i) diff[i].resize(k - i);
}

inline int combine(vector<vector<int>>& a, vector<vector<int>>& b) {
  ll ans = 0, sum = 0;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j <= i; ++j) sum += a[j][i - j];
    for (int j = i; j < k; ++j) ans += sum * b[i][j - i];
  }
  for (int i = 0; i < k; ++i) for (int j = i; j < k; ++j) ans += a[i][j - i] + b[i][j - i];
  return (ans + 1) % MOD;
}

// Solves within range [l, r):
inline void solve(int l, int r) {
  if (l == r - 1) {
    while (qs[l].size()) ans[qs[l].back().second] = 2, qs[l].resize(qs[l].size() - 1);
    return;
  }
  int m = (l + r) >> 1;
  pre[m - 1] = pre[m] = diff;
  pre[m - 1][arr[m - 1]][0] = 1;
  for (int i = m - 2; i >= l; --i) {
    pre[i] = pre[i + 1];
    for (int j = arr[i]; j < k; ++j) for (int r = j; r < k; ++r)
      pre[i][arr[i]][r - arr[i]] += pre[i + 1][j][r - j],
        pre[i][arr[i]][r - arr[i]] -= pre[i][arr[i]][r - arr[i]] >= MOD ? MOD : 0;
    ++pre[i][arr[i]][0];
  }
  pre[m][arr[m]][0] = 1;
  for (int i = m + 1; i < r; ++i) {
    pre[i] = pre[i - 1];
    for (int j = 0; j <= arr[i]; ++j) for (int r = j; r <= arr[i]; ++r)
      pre[i][j][arr[i] - j] += pre[i - 1][j][r - j],
        pre[i][j][arr[i] - j] -= pre[i][j][arr[i] - j] >= MOD ? MOD : 0;
    ++pre[i][arr[i]][0];
  }
  for (int i = l; i < m; ++i) {
    while (qs[i].size() && qs[i].back().first >= m) {
      pii q = qs[i].back(); qs[i].resize(qs[i].size() - 1);
      ans[q.second] = combine(pre[i], pre[q.first]);
    }
  }
  solve(l, m), solve(m, r);
}

int main() {
  ifstream in("nondec.in");
  ofstream out("nondec.out");
  int n; in >> n >> k;
  for (int i = 0; i < n; ++i) in >> arr[i];
  for (int i = 0; i < n; ++i) --arr[i], ans[i] = 0;
  int q; in >> q;
  init(), pre = vector<vector<vector<int>>>(n, diff);
  for (int i = 0; i < q; ++i) {
    int a, b; in >> a >> b; --a, --b;
    qs[a].push_back({b, i});
  }
  for (int i = 0; i < n; ++i) sort(qs[i].begin(), qs[i].end());
  solve(0, n);
  for (int i = 0; i < q; ++i) out << ans[i] << '\n';
  return 0;
}

