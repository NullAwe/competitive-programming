#include <bits/stdc++.h>
using namespace std;

int cnt = 0;

int query(int l, int r, int k) {
  cout << "? " << l << ' ' << r << ' ' << k << endl;
  ++cnt;
  int ans; cin >> ans;
  return ans;
}

int n, diff = -1;
int ans[1026], ans2[1026];

bool has(int i) {
  int a = query(1, i, 2), b = query(i + 1, n, 2);
  ans[i] = a, ans2[i + 1] = b;
  int da = i - a, sa = i - 2 * da;
  int db = n - i - b, sb = n - i - 2 * db;
  if (sa > sb) return true;
  if (sa < sb) return false;
  if (diff >= 0) {
    return diff != 0;
  }
  if (i > 1) {
    int c = query(1, i, n);
    return diff = (c == 1);
  }
  int c = query(i + 1, n, n);
  return diff = (c != 1);
}

int main() {
  cin >> n;
  int cur = 0, done = 0;
  for (int i = 1 << 9; i > 0; i >>= 1) {
    if (cur + i >= n || (done == 9 && n % 2 == 0)) continue;
    ++done;
    if (!has(cur + i)) cur += i;
  }
  if (done == 9 && n % 2 == 0 && cur < n - 1) {
    if (cnt == 20) exit(0);
    int l1 = ans[cur], l2 = ans[cur + 2];
    int r1 = ans2[cur + 3], r2 = ans2[cur + 1];
    if (l2 == l1 + 1) {
      int a = query(1, cur + 1, 2);
      if (a == l1) ++cur;
    } else if (r2 == r1 + 1) {
      int b = query(cur + 2, n, 2);
      if (b == r1 + 1) ++cur;
    } else {
      if (cur) {
        int c = query(1, cur + 1, n);
        if (c == 2) ++cur;
      } else {
        int c = query(cur + 2, n, n);
        if (c == 1) ++cur;
      }
    }
  }
  cout << "! " << cur + 1 << '\n';
  return 0;
}
