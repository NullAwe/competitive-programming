#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX_N = 4e4 + 1;

int ans[MAX_N + 1];

void solve() {
  int n; cin >> n;
  cout << ans[n] << '\n';
}

int main() {
  vector<int> pals; pals.reserve(500);
  for (int i = 1; i < 10; ++i) pals.push_back(i);
  for (int i = 1; i < 100; ++i) {
    int temp = i, fin = i;
    while (temp) {
      fin *= 10;
      fin += temp % 10;
      temp /= 10;
    }
    pals.push_back(fin);
  }
  for (int i = 1; i < 40; ++i) {
    for (int j = 0; j < 10; ++j) {
      int temp = i, fin = i;
      fin *= 10;
      fin += j;
      while (temp) {
        fin *= 10;
        fin += temp % 10;
        temp /= 10;
      }
      pals.push_back(fin);
    }
  }
  sort(pals.begin(), pals.end());
  ans[0] = 1;
  for (int pal : pals) for (int i = pal; i <= MAX_N; ++i) ans[i] = (ans[i] + ans[i - pal]) % MOD;
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
