#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_X = 1000001;

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<bool> sieve(MAX_X);
  vector<int> primes;
  for (int i = 2; i < MAX_X; ++i) {
    if (sieve[i]) continue;
    primes.push_back(i);
    for (int j = i; j < MAX_X; j += i) sieve[j] = true;
  }
  // Reducing every element to not have a perfect square factor:
  for (int i = 0; i < n; ++i) {
    int newX = 1;
    for (int prime : primes) {
      if (prime * prime > arr[i]) break;
      if (arr[i] % prime == 0) newX *= prime;
      while (arr[i] % prime == 0) arr[i] /= prime;
    }
    if (arr[i] > 1) newX *= arr[i];
    arr[i] = newX;
  }
  vector<int> count(1000001);
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    vector<int> factors;
    for (int num : primes) {
      if (num * num > arr[i]) break;
      if (arr[i] % num == 0) {
        factors.push_back(num);
        arr[i] /= num;
      }
    }
    // Adds to the answer using PIE:
    if (arr[i] > 1) factors.push_back(arr[i]);
    for (int i = 0; i < (1 << factors.size()); ++i) {
      int mult = 1, coef = pow(-1, __builtin_popcount(i));
      for (int j = 0; j < factors.size(); ++j)
        if (i & (1 << j)) mult *= factors[j];
      ans += coef * count[mult];
      ++count[mult];
    }
  }
  // Output:
  cout << ans << endl;
  return 0;
}
