#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100001;

vector<int> smallest, largest, ans(MAX_N);

inline bool works(int n, int k) {
  return n % 2 && !(n == 9 && k == 2) && !(k == 1 && smallest[n / 2] == 0) && smallest[n / 2] <= k && k <= largest[n / 2];
}

void dp(int n, int k, int parent, int add) {
  ans[add] = parent;
  if (n == 1) return;
  if (k == 0) {
    dp(n / 2, 0, add, add + 1);
    dp(n / 2, 0, add, add + n / 2 + 1);
  } else if (k == 1) {
    if (__builtin_popcount(n / 2 + 1) == 2) {
      int ind = n / 2, cur = 2;
      for (int tmp = ind + 1; tmp > 0 && tmp % 2 == 0; cur *= 2, tmp >>= 1);
      dp(cur - 1, 0, add, add + 1);
      dp(ind * 2 - cur + 1, 0, add, add + cur);
    } else {
      int tmp, cur = 1;
      for (tmp = n; tmp > 3; cur *= 2, tmp >>= 1);
      cur += cur * (tmp % 2);
      dp(cur - 1, 0, add, add + 1);
      dp(n - cur, k, add, add + cur);
    }
  } else if (works(n - 2, k - 1)) {
    dp(1, 0, add, add + 1);
    dp(n - 2, k - 1, add, add + 2);
  } else {
    dp(3, 0, add, add + 1);
    dp(n - 4, k - 1, add, add + 4);
  }
}

int main() {
  int n, k; cin >> n >> k;
  smallest = vector<int>(n / 2 + 1, 1), largest = vector<int>(n / 2 + 1);
  for (int i = 0; i <= n / 2; ++i) {
    largest[i] = max(i - 1, 0);
  }
  for (int i = 0; (1 << i) - 1 <= n; ++i) smallest[((1 << i) - 1) / 2] = 0;
  if (!works(n, k)) {
    cout << "NO\n";
    return 0;
  }
  dp(n, k, -1, 0);
  cout << "YES\n";
  for (int i = 0; i < n; ++i) cout << ans[i] + 1 << ' ';
  cout << '\n';
  return 0;
}
