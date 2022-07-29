#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> a, b;

inline void add(vector<pii>& doms) {
  for (int i = 0; i < doms.size() / 2; ++i)
    a.push_back(doms[i].first), a.push_back(doms[i].second),
      b.push_back(doms[doms.size() - 1 - i].second), b.push_back(doms[doms.size() - 1 - i].first);
  if (doms.size() & 1)
    a.push_back(doms[doms.size() / 2].first), b.push_back(doms[doms.size() / 2].second);
}

inline void erase(multiset<int>& mult, int num) {
  if (mult.count(num)) mult.erase(mult.find(num));
}

int main() {
  int n; cin >> n;
  vector<pii> doms(n); for (int i = 0; i < n; ++i) cin >> doms[i].first >> doms[i].second;
  for (int i = 0; i < n; ++i) --doms[i].first, --doms[i].second;
  for (int i = 0; i < n; ++i) if (doms[i].first > doms[i].second) swap(doms[i].first, doms[i].second);
  sort(doms.begin(), doms.end());
  vector<int> count(2 * n);
  for (int i = 0; i < n; ++i) {
    ++count[doms[i].first];
    if (doms[i].second > doms[i].first) ++count[doms[i].second];
  }
  for (int i = 0; i < n; ++i) {
    if (count[doms[i].first] == 1 && count[doms[i].second] == 1) {
      cout << -1 << '\n';
      return 0;
    }
  }
  sort(doms.begin(), doms.end());
  vector<multiset<int>> domset(2 * n);
  for (int i = 0; i < n; ++i) {
    domset[doms[i].first].insert(doms[i].second);
    if (doms[i].first != doms[i].second) domset[doms[i].second].insert(doms[i].first);
  }
  vector<bool> done(2 * n), touch(2 * n);
  vector<int> assign(2 * n, -1);
  for (int i = 0; i < 2 * n; ++i) {
    if (domset[i].size() == 1) continue;
    done[i] = true;
    for (int num : domset[i]) if (i != num) erase(domset[num], i), assign[num] = i, touch[num] = true;
  }
  for (int i = 0; i < 2 * n; ++i)
    if (domset[i].size() == 1 && domset[*domset[i].begin()].size() == 1 &&
      assign[*domset[i].begin()] >= 0 && i != *domset[i].begin())
      done[i] = true, domset[i].clear(), assign[i] = -1;
  for (int i = 0; i < 2 * n; ++i)
    if (!done[i] && domset[i].size() == 1)
      erase(domset[assign[i]], i), domset[i].insert(assign[i]), assign[assign[i]] = i;
  vector<vector<pii>> groups;
  done = vector<bool>(2 * n);
  for (int i = 0; i < 2 * n; ++i) {
    if (domset[i].size() != 1) continue;
    vector<pii> group; group.push_back({i, *domset[i].begin()});
    for (int num : domset[assign[i]]) group.push_back({assign[i], num});
    groups.push_back(group);
    done[assign[i]] = true;
  }
  for (int i = 0; i < 2 * n; ++i) {
    if (done[i] || domset[i].size() < 2) continue;
    vector<pii> group;
    for (int num : domset[i]) group.push_back({i, num});
    groups.push_back(group);
  }
  for (vector<pii> group : groups) {
    set<int> starts;
    for (pii dom : group) starts.insert(dom.first);
    vector<pii> td;
    if (starts.size() == 1) {
      for (pii dom : group) td.push_back(dom);
    } else {
      int first = *starts.begin(), other = *--starts.end(), count = 0;
      for (pii dom : group) {
        if ((dom.first == first && dom.second == other) ||
            (dom.second == first && dom.first == other)) ++count;
        else if (dom.first == first) td.push_back(dom);
      }
      for (int i = 0; i < count; ++i) td.push_back({first, other});
      for (pii dom : group) if (dom.first == other && dom.second != first) td.push_back({dom.second, dom.first});
    }
    add(td);
  }
  cout << 2 << ' ' << n << '\n';
  for (int num : a) cout << num + 1 << ' ';
  cout << '\n';
  for (int num : b) cout << num + 1 << ' ';
  cout << '\n';
  string a1, b1;
  for (vector<pii> group : groups) {
    int sz = group.size();
    for (int i = 0; i * 2 + 1 < sz; ++i) a1 += "LR", b1 += "LR";
    if (sz & 1) a1 += "U", b1 += "D";
  }
  cout << a1 << '\n' << b1 << '\n';
  a1.clear(), b1.clear();
  for (vector<pii> group : groups) {
    int sz = group.size();
    a1 += "U", b1 += "D";
    for (int i = 0; i * 2 + 2 < sz; ++i) a1 += "LR", b1 += "LR";
    if (!(sz & 1)) a1 += "U", b1 += "D";
  }
  cout << a1 << '\n' << b1 << '\n';
  return 0;
}
