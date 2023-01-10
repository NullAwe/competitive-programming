#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 529;
const int MAX_K = 23;

int arr[MAX_N][MAX_N];
int help[MAX_K][MAX_K];

void fill() {
  for (int i = 0; i < MAX_K; ++i) for (int j = 1; j < MAX_K; ++j)
    help[i][j] = (help[i][j - 1] + i) % MAX_K;
  for (int i = 0; i < MAX_K; ++i) {
    for (int j = 0; j < MAX_K; ++j) {
      int fi = MAX_K * i, fj = MAX_K * j;
      for (int ii = fi; ii < fi + MAX_K; ++ii) {
        int start = (help[i][j] + ii - fi) % MAX_K;
        for (int jj = 0; jj < MAX_K; ++jj) {
          int ind = fj + start + jj;
          if (ind >= fj + MAX_K) ind -= MAX_K;
          arr[ii][ind] = jj;
        }
      }
    }
  }
}

int main() {
  fill();
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) cout << arr[i][j] + 1 << ' ';
    cout << '\n';
  }
  return 0;
}