#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

int n;
vector<vector<pii>> arr(3);

inline pii con(pair<int, int>& p) { return {p.second, p.first}; }

int solve(vector<int> perm) {
  vector<vector<pii>> parr(3);
  for (int i = 0; i < 3; ++i) parr[i] = arr[perm[i]];
  vector<vector<pii>> vals(3, vector<pii>(n / 3));
  int ans = 0;
  // Vertical:
  // 1
  // 2
  // 3
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < n / 3; ++j) vals[i][j] = con(parr[i][j]);
    sort(vals[i].begin(), vals[i].end()), reverse(vals[i].begin(), vals[i].end());
  }
  int lo = 0, hi = n / 3 + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    int limit = INT_MAX;
    for (int i = 0; i < 3; ++i) {
      int have = 0;
      for (int j = 0; j < n / 3; ++j) {
        if (vals[i][j].first < limit) ++have;
        if (have == mid) {
          limit = vals[i][j].first;
          break;
        }
      }
      if (have < mid) {
        hi = mid;
        break;
      }
    }
    if (hi > mid) lo = mid;
  }
  ans = max(ans, lo);
  // Horizontal:
  // 1 2 3
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < n / 3; ++j) vals[i][j] = parr[i][j];
    sort(vals[i].begin(), vals[i].end());
  }
  lo = 0, hi = n / 3 + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    int limit = INT_MIN;
    for (int i = 0; i < 3; ++i) {
      int have = 0;
      for (int j = 0; j < n / 3; ++j) {
        if (vals[i][j].first > limit) ++have;
        if (have == mid) {
          limit = vals[i][j].first;
          break;
        }
      }
      if (have < mid) {
        hi = mid;
        break;
      }
    }
    if (hi > mid) lo = mid;
  }
  ans = max(ans, lo);
  // Up:
  //  1
  // 2 3
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < n / 3; ++j) vals[i][j] = i ? parr[i][j] : con(parr[i][j]);
    sort(vals[i].begin(), vals[i].end());
    if (!i) reverse(vals[i].begin(), vals[i].end());
  }
  lo = 0, hi = n / 3 + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    int limit = INT_MAX, limit2 = INT_MIN;
    for (int i = 0; i < 3; ++i) {
      int have = 0;
      for (int j = 0; j < n / 3; ++j) {
        if (i) {
          if (vals[i][j].second < limit && vals[i][j].first > limit2) ++have;
          if (have == mid) {
            limit2 = vals[i][j].first;
            break;
          }
        } else {
          ++have;
          if (have == mid) {
            limit = vals[i][j].first;
            break;
          }
        }
      }
      if (have < mid) {
        hi = mid;
        break;
      }
    }
    if (hi > mid) lo = mid;
  }
  ans = max(ans, lo);
  // Right:
  // 2
  //  1
  // 3
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < n / 3; ++j) vals[i][j] = i ? con(parr[i][j]) : parr[i][j];
    sort(vals[i].begin(), vals[i].end()), reverse(vals[i].begin(), vals[i].end());
  }
  lo = 0, hi = n / 3 + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    int limit = INT_MAX, limit2 = INT_MAX;
    for (int i = 0; i < 3; ++i) {
      int have = 0;
      for (int j = 0; j < n / 3; ++j) {
        if (i) {
          if (vals[i][j].second < limit && vals[i][j].first < limit2) ++have;
          if (have == mid) {
            limit2 = vals[i][j].first;
            break;
          }
        } else {
          ++have;
          if (have == mid) {
            limit = vals[i][j].first;
            break;
          }
        }
      }
      if (have < mid) {
        hi = mid;
        break;
      }
    }
    if (hi > mid) lo = mid;
  }
  ans = max(ans, lo);
  // Down:
  // 2 3
  //  1
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < n / 3; ++j) vals[i][j] = i ? parr[i][j] : con(parr[i][j]);
    sort(vals[i].begin(), vals[i].end());
  }
  lo = 0, hi = n / 3 + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    int limit = INT_MIN, limit2 = INT_MIN;
    for (int i = 0; i < 3; ++i) {
      int have = 0;
      for (int j = 0; j < n / 3; ++j) {
        if (i) {
          if (vals[i][j].second > limit && vals[i][j].first > limit2) ++have;
          if (have == mid) {
            limit2 = vals[i][j].first;
            break;
          }
        } else {
          ++have;
          if (have == mid) {
            limit = vals[i][j].first;
            break;
          }
        }
      }
      if (have < mid) {
        hi = mid;
        break;
      }
    }
    if (hi > mid) lo = mid;
  }
  ans = max(ans, lo);
  // Left:
  //  2
  // 1
  //  3
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < n / 3; ++j) vals[i][j] = i ? con(parr[i][j]) : parr[i][j];
    sort(vals[i].begin(), vals[i].end());
    if (i) reverse(vals[i].begin(), vals[i].end());
  }
  lo = 0, hi = n / 3 + 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    int limit = INT_MIN, limit2 = INT_MAX;
    for (int i = 0; i < 3; ++i) {
      int have = 0;
      for (int j = 0; j < n / 3; ++j) {
        if (i) {
          if (vals[i][j].second > limit && vals[i][j].first < limit2) ++have;
          if (have == mid) {
            limit2 = vals[i][j].first;
            break;
          }
        } else {
          ++have;
          if (have == mid) {
            limit = vals[i][j].first;
            break;
          }
        }
      }
      if (have < mid) {
        hi = mid;
        break;
      }
    }
    if (hi > mid) lo = mid;
  }
  ans = max(ans, lo);
  return ans;
}

int main() {
  cin >> n;
  for (int i = 0; i < 3; ++i) arr[i].reserve(n / 3);
  for (int i = 0; i < n; ++i) {
    int x, y, c; cin >> x >> y >> c; --c;
    arr[c].push_back({x, y});
  }
  int ans = 0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; ++k) {
        if (i == j || i == k || j == k) continue;
        vector<int> perm = {i, j, k};
        ans = max(ans, solve(perm));
      }
    }
  }
  cout << 3 * ans << '\n';
  return 0;
}
