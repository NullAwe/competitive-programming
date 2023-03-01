#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define x first
#define y second

const int MAX_N = 200;

int n, k;
pii points[MAX_N];
ll shoelace[MAX_N + 1];
int dp[MAX_N][MAX_N];

inline ll get(int a, int b) {
  return (ll) points[a].x * points[b].y - (ll) points[a].y * points[b].x;
}

inline ll sum(int l, int r) {
  return l > r ? shoelace[n] - shoelace[l] + shoelace[r] :
          shoelace[r] - shoelace[l];
}

inline ll area(int l1, int r1, int l2, int r2) {
  return sum(l1, r1) + get(r1, l2) + sum(l2, r2) + get(r2, l1);
}

inline int sections(ll minA) {
  for (int diff = 2; diff < n; ++diff) {
    for (int l = 0; l < n; ++l) {
      int r = (diff + l) % n;
      dp[l][r] = 0;
      int end = (l > r) ? r + n : r, hi = l;
      while (hi <= end && area(l, hi % n, r, r) < minA) ++hi;
      int top = r;
      if (hi <= end) {
        hi %= n;
        while (true) {
          dp[l][r] = max(dp[l][r], dp[hi][top] + 1);
          if (top == l) break;
          if (top == hi) hi = (hi == 0 ? n - 1 : hi - 1);
          top = (top == 0 ? n - 1 : top - 1);
          while (hi > l && area(l, hi == 0 ? n - 1 : hi - 1, top, r) >= minA) --hi;
        }
      }
      for (int mid = (l == n - 1 ? 0 : l + 1); mid != r; mid = (mid == n - 1 ? 0 : mid + 1)) {
        ll area = get(l, mid) + get(mid, r) + get(r, l);
        if (area >= minA) dp[l][r] = max(dp[l][r], dp[l][mid] + dp[mid][r] + 1);
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ans = max(ans, dp[i][j]);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> k;
  for (int i = 0; i < n; ++i) cin >> points[i].first >> points[i].second;
  for (int i = 1; i <= n; ++i) shoelace[i] = shoelace[i - 1] + get(i - 1, i % n);
  ll lo = 0, hi = 1LL << 62;
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    if (sections(mid) <= k) hi = mid;
    else lo = mid;
  }
  cout << lo << '\n';
  return 0;
}
