#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 2750132, MAX_N = 200000;

int main() {
  int n; cin >> n;
  vector<int> nums(MAX_SIZE);
  for (int i = 0; i < 2 * n; ++i) {
    int num;
    cin >> num;
    ++nums[num];
  }
  // Finds the first (MAX_N - 1) prime numbers:
  vector<bool> sieve(MAX_SIZE);
  vector<int> primes(MAX_N);
  int ind = -1;
  for (int i = 2; ind < MAX_N - 1; ++i) {
    if (sieve[i]) continue;
    primes[++ind] = i;
    for (int j = i; j < MAX_SIZE; j += i) sieve[j] = true;
  }
  vector<int> ans(n);
  ind = -1;
  // Inflates n with all the composite numbers:
  for (int i = MAX_SIZE - 1; i >= 0; --i) {
    if (nums[i] == 0) continue;
    int least = 1, tmp = i;
    for (int j = 2; j * j <= tmp; ++j) {
      if (tmp % j == 0) {
        if (least == 1) least = j;
        while (tmp % j == 0) tmp /= j;
      }
    }
    if (least == 1) continue;
    while (nums[i] > 0) {
      ans[++ind] = i;
      --nums[i];
      --nums[i / least];
    }
  }
  // Inflates n with all the prime numbers:
  for (int i = 0; i < MAX_SIZE; ++i) {
    if (nums[i] == 0) continue;
    while (nums[i] > 0) {
      ans[++ind] = i;
      --nums[i];
      --nums[primes[i - 1]];
    }
  }
  // Output:
  for (int num : ans) cout << num << " ";
  cout << endl;
  return 0;
}
