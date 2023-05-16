#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pil pair<int, ll>

const int LG = 62;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> vals(n);
  vector<ll> masks(n);
  for (int i = 0; i < n; ++i) cin >> vals[i] >> masks[i];
  vector<vector<pil>> brackets(62);
  for (int i = 0; i < n; ++i) {
    for (int j = 61; j >= 0; --j) {
      if (masks[i] - (1LL << j) >= 0) {
        brackets[j].push_back({vals[i], masks[i]});
        break;
      }
    }
  }
  ll total = 0, tot = 0, ans = 0; for (int i = 0; i < n; ++i) total += vals[i];
  for (int i = 0; i < 62; ++i) {
    ll sum = 0;
    for (pil num : brackets[i]) sum += ((__builtin_popcountll(num.second & ans) & 1) ? -1 : 1) * num.first;
    if (((total >= 0) == (sum + tot >= 0) || sum + tot == 0) && sum != 0) ans |= (1LL << i), tot -= sum;
    else tot += sum;
  }
  cout << ans << '\n';
  return 0;
}