#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll sum = 0;
  for (int num : arr) sum += num;
  if (sum % n > 0) {
    cout << "No\n";
    return;
  }
  int avg = (int) (sum / n);
  vector<int> add, sub;
  multiset<int> p2a, p2s;
  int same = 0;
  for (int num : arr) {
    int diff = num - avg;
    if (diff == 0) continue;
    if (diff > 0 && __builtin_popcount(diff) == 1) p2a.insert(diff);
    else if (diff < 0 && __builtin_popcount(-diff) == 1) p2s.insert(-diff);
    bool can = false;
    for (int s = 0; s < 31; ++s) {
      ll nd = (ll) diff + (1 << s);
      if (nd > INT_MAX) continue;
      if (nd > 0 && __builtin_popcount((int) nd) == 1) {
        can = true;
        add.push_back(nd), sub.push_back(1 << s);
      }
    }
    if (!can) {
      cout << "No\n";
      return;
    }
  }
  multiset<int> adds, subs;
  for (int num : add) adds.insert(num);
  for (int num : sub) subs.insert(num);
  while (adds.size() && subs.size()) {
    int af = *adds.begin(), sf = *subs.begin();
    if (af == sf) {
      adds.erase(adds.begin()), subs.erase(subs.begin());
      continue;
    }
    if (af > sf) {
      if (af != sf * 2 || !p2a.count(sf)) {
        cout << "No\n";
        return;
      }
      p2a.erase(p2a.find(sf));
      adds.erase(adds.begin()), subs.erase(subs.begin());
      adds.insert(sf);
    } else {
      if (sf != af * 2 || !p2s.count(af)) {
        cout << "No\n";
        return;
      }
      p2s.erase(p2s.find(af));
      adds.erase(adds.begin()), subs.erase(subs.begin());
      subs.insert(af);
    }
  }
  cout << "Yes\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
