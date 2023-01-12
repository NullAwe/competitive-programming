#include <iostream>
#include <vector>
using namespace std;

int query(int w) {
  cout << "? " << w << endl;
  int ans; cin >> ans;
  return ans;
}

int main() {
  int n; cin >> n;
  int at = 0;
  for (int i = 21; i >= 0; --i) {
    int ans = query(at + (1 << i));
    if (ans != 1) at += (1 << i);
  }
  ++at;
  int ans = at;
  for (int h = 2; h <= n; ++h) {
    int w = query(at / h);
    if (w) ans = min(ans, w * (at / h));
  }
  cout << "! " << ans << endl;
  return 0;
}
