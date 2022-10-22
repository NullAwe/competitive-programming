#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int INF = 1e9, NINF = -INF;

struct Cow {

  int t, p, w;

  Cow() {}

  Cow(int t, int p, int w) : t(t), p(p), w(w) {}
};

int n, k;
vector<Cow> cows;

int solve1() {
  vector<pii> gs, hs;
  for (Cow cow : cows) {
    if (!cow.t) gs.push_back({cow.p, cow.w});
    else hs.push_back({cow.p, cow.w});
  }
  n = gs.size(); int m = hs.size();
  int dp[n + 1][m + 1][4];
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) for (int l = 0; l < 4; ++l) dp[i][j][l] = INF;
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    dp[i + 1][0][0] = sum + gs[i].second, dp[i + 1][0][2] = sum;
    sum += gs[i].second;
  }
  sum = 0;
  for (int j = 0; j < m; ++j) {
    dp[0][j + 1][0] = sum + hs[j].second, dp[0][j + 1][1] = sum;
    sum += hs[j].second;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int i1 = i + 1, j1 = j + 1, diff = abs(gs[i].first - hs[j].first);
      for (int l = 0; l < 4; ++l) {
        if (!l && diff <= k) continue;
        if (l == 3 && diff > k) continue;
        dp[i1][j1][l] = min(dp[i1][j1][l], min(dp[i][j][0], dp[i][j][3]));
        if (l & 1) dp[i1][j1][l] = min(dp[i1][j1][l], dp[i][j1][1]);
        if (l & 2) dp[i1][j1][l] = min(dp[i1][j1][l], dp[i1][j][2]);
        if (!(l & 1)) dp[i1][j1][l] += hs[j].second;
        if (!(l & 2)) dp[i1][j1][l] += gs[i].second;
        dp[i1][j1][l] = min(dp[i1][j1][l], INF);
      }
    }
  }
  int ans = INF;
  sum = 0;
  for (int i = 0; i < n; ++i) sum += gs[i].second;
  for (int i = 0; i < n; ++i) {
    sum -= gs[i].second;
    ans = min(ans, min(dp[i + 1][m][0], dp[i + 1][m][3]) + sum);
  }
  sum = 0;
  for (int j = 0; j < m; ++j) sum += hs[j].second;
  for (int j = 0; j < m; ++j) {
    sum -= hs[j].second;
    ans = min(ans, min(dp[n][j + 1][0], dp[n][j + 1][3]) + sum);
  }
  return ans;
}

int solve2() {
  vector<pii> gs, hs;
  for (Cow cow : cows) {
    if (!cow.t) gs.push_back({cow.p, cow.w});
    else hs.push_back({cow.p, cow.w});
  }
  n = gs.size(); int m = hs.size();
  int dp[n + 1][m + 1][2];
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) for (int l = 0; l < 2; ++l) dp[i][j][l] = NINF;
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += gs[i].second;
    dp[i + 1][0][0] = sum;
  }
  sum = 0;
  for (int j = 0; j < m; ++j) {
    sum += hs[j].second;
    dp[0][j + 1][1] = sum;
  }
  dp[0][0][0] = dp[0][0][1] = 0;
  int reach[n + 1][m + 1];
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) reach[i][j] = -1;
  for (int i = n - 1; i >= 0; --i) for (int j = m - 1; j >= 0; --j) {
    if (reach[i + 1][j + 1] > 1) {
      reach[i][j] = reach[i + 1][j + 1] - 1;
      continue;
    }
    int sub;
    for (sub = 0; i - sub >= 0 && j - sub >= 0; ++sub) if (abs(gs[i - sub].first - hs[j - sub].first) > k) break;
    reach[i][j] = sub;
  }
  int outH[n + 1], outG[m + 1];
  for (int i = 0; i <= n; ++i) outH[i] = 0;
  for (int i = 0; i <= m; ++i) outG[i] = 0;
  for (int i = 0; i < n; ++i) {
    outH[i + 1] = outH[i];
    while (outH[i + 1] < m && hs[outH[i + 1]].first < gs[i].first - k) ++outH[i + 1];
  }
  for (int i = 0; i < m; ++i) {
    outG[i + 1] = outG[i];
    while (outG[i + 1] < n && gs[outG[i + 1]].first < hs[i].first - k) ++outG[i + 1];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int i1 = i + 1, j1 = j + 1, diff = abs(gs[i].first - hs[j].first);
      for (int l = 0; l < 2; ++l) {
        if (diff <= k) dp[i1][j1][l] = dp[i][j][l];
        dp[i1][j1][l] = max(dp[i1][j1][l], dp[i1 - (1 - l)][j1 - l][l] + (l ? hs[j].second : gs[i].second));
        if (dp[i1][j1][l] < 0) dp[i1][j1][l] = NINF;
        if (!l) {
          int hout = outH[i1];
          int bef = i ? j - reach[i - 1][j] : -1;
          if (i1 - j1 + hout - 1 >= 0 && hout <= j1 && hout > bef) dp[i1][j1][l] = max(dp[i1][j1][l], dp[i1 - j1 + hout - 1][hout][1] + gs[i].second);
        } else {
          int gout = outG[j1];
          int bef = j ? i - reach[i][j - 1] : -1;
          if (j1 - i1 + gout - 1 >= 0 && gout <= i1 && gout > bef) dp[i1][j1][l] = max(dp[i1][j1][l], dp[gout][j1 - i1 + gout - 1][0] + hs[j].second);
        }
        if (dp[i1][j1][l] < 0) dp[i1][j1][l] = NINF;
      }
    }
  }
  return max(max(dp[n][m][0], dp[n][m][1]), 0);
}

int main() {
  int t; cin >> t >> n >> k;
  cows.resize(n);
  for (int i = 0; i < n; ++i) {
    char type; cin >> type;
    int pos, weight; cin >> pos >> weight;
    cows[i] = Cow(type == 'H', pos, weight);
  }
  if (t == 1) cout << solve1() << '\n';
  else cout << solve2() << '\n';
  return 0;
}
