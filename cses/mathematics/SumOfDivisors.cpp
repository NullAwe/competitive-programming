#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

int main() {
  long long n;
  cin >> n;
  vector<vector<long long>> pairs((int) sqrt(n) * 2 + 1, vector<long long>(2, 0));
  for (long long i = 1; i * i <= n; ++i) {
    int ind = (i - 1) * 2;
    pairs[ind][0] = n / i;
    pairs[ind][1] = n % i;
    pairs[ind + 1][0] = n / (n / i);
    pairs[ind + 1][1] = n % (n / i);
  }
  sort(pairs.begin(), pairs.end());
  std::reverse(pairs.begin(), pairs.end());
  long long minus = 0;
  for (int i = 0; i < pairs.size() - 1; ++i) {
    vector<long long> a = pairs[i], b = pairs[i + 1];
    long long num = a[0] - b[0] - 1, base = ((n / a[0]) % MOD) * (((num % MOD) * ((num + 1) % MOD) / 2) % MOD);
    base %= MOD;
    base += ((a[1] % MOD) * ((num + 1) % MOD)) % MOD;
    minus += base;
    minus %= MOD;
  }
  n %= MOD;
  long long ans = (n * n) % MOD;
  ans = (ans - minus + MOD) % MOD;
  cout << ans;
  return 0;
}

