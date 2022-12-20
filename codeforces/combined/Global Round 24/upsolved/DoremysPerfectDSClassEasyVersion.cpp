#include <bits/stdc++.h>
using namespace std;

int query(int l, int r, int k) {
  cout << "? " << l << ' ' << r << ' ' << k << endl;
  int ans; cin >> ans;
  return ans;
}

int n;

bool has(int i) {
  int a = query(1, i, 2), b = query(i + 1, n, 2);
  int da = i - a, sa = i - 2 * da;
  int db = n - i - b, sb = n - i - 2 * db;
  if (sa > sb) return true;
  if (sa < sb) return false;
  if (i > 1) {
    int c = query(1, i, n);
    return c == 1;
  }
  int c = query(i + 1, n, n);
  return c != 1;
}

int main() {
  cin >> n;
  int cur = 0;
  for (int i = 1 << 10; i > 0; i >>= 1) {
    if (cur + i >= n) continue;
    if (!has(cur + i)) cur += i;
  }
  cout << "! " << cur + 1 << '\n';
  return 0;
}
