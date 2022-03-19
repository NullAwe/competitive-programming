#include <bits/stdc++.h>
using namespace std;

int query(int a, int b, int c) {
  printf("? %d %d %d\n", a, b, c); fflush(stdout);
  int res; scanf("%d", &res);
  return res;
}

void output(int a, int b) {
  printf("! %d %d\n", a, b); fflush(stdout);
}

void solve() {
  int n; cin >> n;
  vector<int> res(2 * n - 5), extra(2 * n - 5);
  int m = 0, ind = 0;
  for (int i = 3; i <= n; ++i) {
    res[i - 3] = query(1, 2, i);
    if (res[i - 3] >= m) {
      m = res[i - 3];
      ind = i;
    }
    extra[i - 3] = i;
  }
  int cur = n - 2;
  for (int i = n; i > 2; --i) {
    if (i == ind) continue;
    res[cur] = query(1, ind, i);
    if (res[cur] > m) m = res[cur];
    extra[cur] = i;
    ++cur;
  }
  int mInd = 0, a, b, c;
  for (int i = 0; i < n - 2; ++i) {
    if (res[i] == m) {
      mInd = i, a = 1, b = 2, c = extra[i];
      break;
    }
  }
  for (int i = n - 2; i < 2 * n - 5; ++i) {
    if (res[i] == m) {
      mInd = i, a = 1, b = ind, c = extra[i];
      break;
    }
  }
  int d;
  if (a + b + c == 6) d = 4;
  else if (b != 2) d = 2;
  else d = 3;
  int ab = query(a, b, d), ac = query(a, c, d), bc = query(b, c, d);
  if (ab != m && ac != m) output(b, c);
  else if (ab != m && bc != m) output(a, c);
  else if (ac != m && bc != m) output(a, b);
  else if (ab != m) output(c, d);
  else if (ac != m) output(b, d);
  else output(a, d);
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
