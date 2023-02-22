#include <iostream>
using namespace std;

void solve() {
  int n; cin >> n;
  int alice = (n + 1) / 2;
  int e = 0, o = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    if (x & 1) ++o;
    else ++e;
  }
  if (n & 1) {
    int p = o & 1;
    if (p) {
      if (e) {
        if (o % 2 == 0 && o % 4 > 0) {
          cout << "Alice\n";
          return;
        }
      }
      if (o) {
        --o;
        if (o % 2 == 0 && o % 4 > 0) {
          cout << "Alice\n";
          return;
        }
      }
      cout << "Bob\n";
    } else {
      if (e) {
        if (o % 2 == 0 && o % 4 == 0) {
          cout << "Alice\n";
          return;
        }
      }
      if (o) {
        --o;
        if (o % 2 == 0 && o % 4 == 0) {
          cout << "Alice\n";
          return;
        }
      }
      cout << "Bob\n";
    }
  } else {
    if (o % 2 == 0 && o % 4 > 0) cout << "Bob\n";
    else cout << "Alice\n";
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
