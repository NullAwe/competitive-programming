#include <bits/stdc++.h>
using namespace std;

int qry(int a, int b) {
  cout << "? " << a + 1 << ' ' << b + 1 << endl;
  int x; cin >> x;
  return x;
}

int main() {
  int n; cin >> n;
  vector<int> ans(n);
  vector<int> order(n); for (int i = 0; i < n; ++i) order[i] = i;
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(order.begin(), order.end(), default_random_engine(seed));
  int a1 = order[0], a2 = order[1];
  int tog = qry(a1, a2);
  bool sure = true;
  for (int xx = 2; xx < n; ++xx) {
    if (rand() % 2 == 1) swap(a1, a2);
    int i = order[xx];
    int t1 = qry(a1, i);
    if (sure) {
      if (tog > t1) {
        ans[i] = t1;
        continue;
      }
      if (t1 > tog) {
        ans[a2] = tog;
        a2 = i;
        tog = t1;
        continue;
      }
      ans[a1] = tog;
      a1 = i, sure = false;
    } else {
      if (tog > t1) {
        ans[i] = t1;
        continue;
      }
      int t2 = qry(a2, i);
      if (t1 == t2) {
        ans[i] = tog = t1;
        continue;
      }
      sure = true;
      if (t1 > t2) {
        ans[a2] = t2;
        a2 = i, tog = t1;
      } else {
        ans[a1] = t1;
        a1 = i, tog = t2;
      }
    }
  }
  if (!sure) tog = qry(a1, a2);
  ans[a1] = ans[a2] = tog;
  cout << "!";
  for (int num : ans) cout << ' ' << num;
  cout << endl;
  return 0;
}