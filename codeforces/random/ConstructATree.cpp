#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  ll n, x; cin >> n >> x;
  if (n * (n + 1) / 2 < x || x < n * 2 - 1) {
    cout << "No\n";
    return 0;
  }
  cout << "Yes\n";
  ll lo = 0, hi = n;
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    ll sum = 0, level = 1, mult = 1, used = 0;
    while (used < n) {
      sum += level * min(mult, n - used);
      ++level;
      used += min(mult, n - used);
      mult *= mid;
    }
    if (sum > x) lo = mid;
    else hi = mid;
  }
  if (hi == 1) {
    for (int i = 1; i < n; ++i) cout << i << ' ';
    cout << '\n';
    return 0;
  }
  vector<int> last = {1}; ll on = 2;
  --x;
  for (int level = 2; x > 0; ++level) {
    ll lo2 = 0, hi2 = min((ll) last.size() * hi, n - on + 1) + 1;
    while (lo2 < hi2 - 1) {
      ll mid = (lo2 + hi2) / 2;
      ll have = n - on + 1 - mid;
      ll sum = mid * level + ((level + 1) + (level + have)) * have / 2;
      if (sum >= x) lo2 = mid;
      else hi2 = mid;
    }
    vector<int> cur(lo2);
    for (int i = 0; i < lo2; ++i) {
      // Output:
      cout << last[i / hi] << ' ';
      cur[i] = on + i;
    }
    on += lo2;
    last = cur;
    x -= level * lo2;
  }
  cout << '\n';
  return 0;
}
