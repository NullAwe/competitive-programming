#include <bits/stdc++.h>
using namespace std;

int n, q, against, now, x[200001];

int main() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
    x[i] ^= x[i - 1];
  }
  for (int i = 0; i < q; i++) {
    cin >> against >> now; --against;
    cout << (x[now] ^ x[against]) << "\n";
  }
  return 0;
}

