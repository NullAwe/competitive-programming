#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007, MAX_X = 5000001;

vector<int> composite(MAX_X, 0), primes;

void solve() {
  int n; cin >> n;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<ll> mults(MAX_X);
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j * j <= arr[i]; ++j) {
      if (arr[i] % j) continue;
      ++mults[j];
      if (j * j != arr[i]) ++mults[arr[i] / j];
    }
  }
  vector<ll> memo(MAX_X);
  memo[1] = mults[1];
  for (int i = 2; i < MAX_X; ++i) {
    if (!composite[i]) {
      memo[i] = memo[1] + (i - 1) * mults[i];
    } else {
      int temp = i;
      for (int num : primes) {
        if (num * num > temp) break;
        if (temp % num == 0) {
          temp /= num;
          memo[i] = max(memo[i], memo[i / num] + (i - i / num) * mults[i]);
          while (temp % num == 0) temp /= num;
        }
      }
      if (temp > 1) memo[i] = max(memo[i], memo[i / temp] + (i - i / temp) * mults[i]);
    }
  }
  // Output:
  ll ans = 0;
  for (ll num : memo) ans = max(ans, num);
  cout << ans << endl;
}

int main() {
  for (int i = 2; i < MAX_X; ++i) {
    if (!composite[i]) {
      composite[i] = i;
      primes.push_back(i);
    }
    for (int j = 0; j < primes.size() && primes[j] <= composite[i] && i * primes[j] <= MAX_X; ++j) {
      composite[i * primes[j]] = primes[j];
    }
  }
  solve();
  return 0;
}
