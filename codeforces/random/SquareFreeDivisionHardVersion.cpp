#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <set>
using namespace std;

void update(vector<int>& t, int n, int p, int v) {
  for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(vector<int>& t, int n, int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

void solve() {
  int n, k; cin >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  map<vector<int>, int> m;
  int id = 1;
  for (int i = 0; i < n; ++i) {
    vector<int> primes;
    for (int j = 2; j * j <= arr[i]; ++j) {
      if (arr[i] % j == 0) {
        int divs;
        for (divs = 0; arr[i] % j == 0; divs += 1, arr[i] /= j);
        if (divs & 1) primes.push_back(j);
      }
    }
    if (arr[i] > 1) primes.push_back(arr[i]);
    int val = m[primes]; if (!val) m[primes] = val = id++;
    arr[i] = val;
  }
  vector<int> t(2 * n);
  map<int, int> places;
  vector<pair<int, int>> dp(k + 1, {0, 1});
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= k; ++j) {
      if (j && (dp[j].second < dp[j - 1].second ||
            (dp[j].second < dp[j - 1].second && dp[j].first < dp[j - 1].first))) dp[j - 1] = dp[j];
      if (places[arr[i]] && query(t, n, places[arr[i]], i) < dp[j].first) dp[j] = {1, dp[j].second + 1};
      else ++dp[j].first;
    }
    if (places[arr[i]]) update(t, n, places[arr[i]] - 1, 0);
    places[arr[i]] = i + 1;
    update(t, n, places[arr[i]] - 1, 1);
  }
  cout << dp[0].second << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
