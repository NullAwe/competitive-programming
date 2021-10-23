#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll oo = 1000000000000000;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  ll n, a, b; cin >> n >> a >> b;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<ll> nums(6);
  for (int j = -1; j < 2; ++j) nums[j + 1] = arr[0] + j;
  for (int j = -1; j < 2; ++j) nums[3 + j + 1] = arr[n - 1] + j;
  set<ll> primes;
  for (ll num : nums) {
    for (ll i = 2; i * i <= num; ++i) {
      if (num % i == 0) primes.insert(i);
      while (num % i == 0) num /= i;
    }
    if (num > 1) primes.insert(num);
  }
  ll ans = oo;
  for (ll prime : primes) {
    // Finds answer using dynamic programming:
    vector<vector<ll>> memo(n + 1, vector<ll>(3, -1));
    memo[0][0] = memo[0][1] = memo[0][2] = 0;
    for (int ind = 1; ind <= n; ++ind) {
      ll cost = ((arr[ind - 1] + 1) % prime) > 2 ? oo : (arr[ind - 1] % prime ? b : 0);
      memo[ind][0] = min(oo, memo[ind - 1][0] + cost);
      memo[ind][1] = min(oo, a + min(memo[ind - 1][0], memo[ind - 1][1]));
      memo[ind][2] = min(oo, cost + min(memo[ind - 1][1], memo[ind - 1][2]));
    }
    ans = min(ans, min(memo[n][0], min(memo[n][1], memo[n][2])));
  }
  // Output:
  cout << ans << endl;
}
