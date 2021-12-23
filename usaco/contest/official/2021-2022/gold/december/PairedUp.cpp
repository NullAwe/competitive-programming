#include <bits/stdc++.h>
using namespace std;

int d(int type) { return type == 1 ? INT_MAX - 1 : -1; }

int z(int a, int b, int type) { return type == 1 ? min(a, b) : max(a, b); }

int dp(int ind, int choice, vector<int>& front, vector<int>& w, vector<vector<int>>& memo, int t) {
  if (ind >= memo.size()) return 0;
  if (memo[ind][choice] < INT_MAX) return memo[ind][choice];
  int f = front[ind];
  if (choice == 0) {
    if ((f - ind) % 2 == 0) {
      int m = z(dp(f + 1, 0, front, w, memo, t), z(dp(f + 1, 1, front, w, memo, t),
          dp(f + 1, 2, front, w, memo, t), t), t);
      if (m == d(t)) memo[ind][choice] = d(t);
      else memo[ind][choice] = w[ind] + m;
    } else {
      int m = z(dp(f, 1, front, w, memo, t), dp(f, 2, front, w, memo, t), t);
      if (m == d(t)) memo[ind][choice] = d(t);
      else memo[ind][choice] = w[ind] + m;
    }
  } else if (choice == 1) {
    if (f == ind) memo[ind][choice] = d(t);
    else memo[ind][choice] = z(dp(ind + 2, 0, front, w, memo, t), z(dp(ind + 2, 1, front, w, memo, t),
        dp(ind + 2, 2, front, w, memo, t), t), t);
  } else if (choice == 2) {
    if (f <= ind + 1) memo[ind][choice] = d(t);
    else memo[ind][choice] = dp(ind + 1, 3, front, w, memo, t);
  } else {
    if (f == ind) {
      int m = z(dp(ind + 2, 0, front, w, memo, t), z(dp(ind + 2, 1, front, w, memo, t),
          dp(ind + 2, 2, front, w, memo, t), t), t);
      if (m == d(t)) memo[ind][choice] = d(t);
      else memo[ind][choice] = w[ind] + m;
    } else {
      if ((f - ind) % 2 == 1) {
        int m = z(dp(f + 1, 0, front, w, memo, t), z(dp(f + 1, 1, front, w, memo, t),
            dp(f + 1, 2, front, w, memo, t), t), t);
        if (m == d(t)) memo[ind][choice] = d(t);
        else memo[ind][choice] = w[ind] + m;
      } else {
        int m = z(dp(f, 1, front, w, memo, t), dp(f, 2, front, w, memo, t), t);
        if (m == d(t)) memo[ind][choice] = d(t);
        else memo[ind][choice] = w[ind] + m;
      }
    }
  }
  return memo[ind][choice];
}

int main() {
  int t, n, k; cin >> t >> n >> k;
  vector<pair<int, int>> lw(n);
  for (int i = 0; i < n; ++i) cin >> lw[i].first >> lw[i].second;
  sort(lw.begin(), lw.end());
  vector<int> l(n), w(n);
  for (int i = 0; i < n; ++i) l[i] = lw[i].first, w[i] = lw[i].second;
  vector<int> back(n), front(n);
  int b = 0;
  for (int i = 0; i < n; ++i) {
    while (l[i] - l[b] > k) ++b;
    back[i] = b;
  }
  int f = n - 1;
  for (int i = n - 1; i >= 0; --i) {
    while (l[f] - l[i] > k) --f;
    front[i] = f;
  }
  vector<vector<int>> memo(n, vector<int>(4, INT_MAX));
  // Output:
  cout << z(dp(0, 0, front, w, memo, t), z(dp(0, 1, front, w, memo, t),
      dp(0, 2, front, w, memo, t), t), t) << endl;
  return 0;
}
