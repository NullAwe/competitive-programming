#include <iostream>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  int moves[k]; for (int i = 0; i < k; ++i) cin >> moves[i];
  bool status[n + 1]; status[0] = 0;
  for (int i = 1; i <= n; ++i) {
    status[i] = 0;
    for (int m : moves) {
      if (i - m < 0) continue;
      status[i] |= 1 - status[i - m];
    }
  }
  for (int i = 1; i <= n; ++i) cout << (status[i] ? 'W' : 'L');
  cout << '\n';
  return 0;
}

