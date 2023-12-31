#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve() {
  int n, m, k; cin >> n >> m >> k;
  vector<int> arr(m); for (int i = 0; i < m; ++i) cin >> arr[i];
  for (int i = 0; i < m; ++i) --arr[i];
  vector<int> lst(m, m);
  vector<int> nxt(m);
  for (int i = m - 1; i >= 0; --i) {
    nxt[i] = lst[arr[i]];
    lst[arr[i]] = i;
  }
  vector<deque<int>> stacks(n);
  unordered_set<int, custom_hash> emp, one, inc; for (int i = 0; i < n; ++i) emp.insert(i);
  set<pii> ones;
  vector<int> locs(k, -1), nxc(k, -1);
  vector<vector<int>> ans;
  vector<int> ad;
  for (int i = 0; i < m; ++i) {
    assert((int) ans.size() <= 2 * m);
    int l = locs[arr[i]];
    if (l > -1) {
      if (stacks[l].back() == arr[i]) {
        stacks[l].pop_back();
        ad = {1, l + 1};
      } else {
        assert(stacks[l].front() == arr[i]);
        assert(!emp.empty());
        stacks[l].pop_front();
        int v = *emp.begin();
        ad = {1, v + 1};
        ans.push_back(ad);
        ad = {2, l + 1, v + 1};
      }
      if (stacks[l].empty()) emp.insert(l), one.erase(l);
      else if ((int) stacks[l].size() == 1)
        one.insert(l), ones.insert({nxc[stacks[l].front()], l}), inc.erase(l);
      else if (nxc[stacks[l].front()] < nxc[stacks[l].back()]) inc.insert(l);
      locs[arr[i]] = -1;
    } else {
      if ((int) emp.size() > 1) l = *emp.begin();
      else if (!emp.empty() && one.size()) l = *one.begin();
      else if (emp.empty()) l = (--ones.end())->second;
      else if (inc.empty()) l = *emp.begin();
      else l = *inc.begin();
      if (emp.count(l)) emp.erase(l), one.insert(l), ones.insert({nxt[i], l});
      else if (one.count(l)) {
        one.erase(l), ones.erase({nxc[stacks[l].front()], l});
        if (nxc[stacks[l].front()] < nxt[i]) inc.insert(l);
      } else inc.erase(l);
      stacks[l].push_back(arr[i]);
      locs[arr[i]] = l;
      nxc[arr[i]] = nxt[i];
      ad = {1, l + 1};
    }
    ans.push_back(ad);
  }
  cout << (int) ans.size() << '\n';
  for (vector<int> v : ans) {
    for (int num : v) cout << num << ' ';
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
  return 0;
}