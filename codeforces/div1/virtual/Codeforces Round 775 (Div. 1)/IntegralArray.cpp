#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, c; cin >> n >> c;
  bool has[c + 1]; for (int i = 0; i <= c; ++i) has[i] = false;
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    has[a] = true;
  }
  int prefix[c + 1]; prefix[0] = 0; for (int i = 1; i <= c; ++i) prefix[i] = prefix[i - 1] + has[i];
  for (int i = 1; i <= c; ++i) {
    if (!has[i]) continue;
    for (int j = 1; j * i <= c; ++j) {
      if (has[j]) continue;
      int smallest = i * j, largest = min((j + 1) * i - 1, c);
      if (prefix[largest] - prefix[smallest - 1]) {
        cout << "No\n";
        return;
      }
    }
  }
  cout << "Yes\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
