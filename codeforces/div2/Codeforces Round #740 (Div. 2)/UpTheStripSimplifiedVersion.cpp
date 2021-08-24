#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, m; cin >> n >> m;
  vector<ll> memo(n + 1);
  memo[1] = 1;
  ll sum = 1;
  for (int i = 2; i <= n; ++i) {
    // Takes care of the subtraction operations in O(1) time:
    memo[i] = sum;
    // Takes care of the division operations in O(sqrt(n)) time:
    int last = 1;
    for (int j = 2, k; j <= i; j = k) {
      int floored = i / j;
      int num = i / floored - last;
      memo[i] += num * memo[floored];
      memo[i] %= m;
      k = j + num;
      last = k - 1;
    }
    sum += memo[i];
    sum %= m;
  }
  // Output:
  cout << memo[n] << endl;
  return 0;
}
