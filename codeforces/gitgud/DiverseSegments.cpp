#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

set<pii> larg;
vector<vector<int>> groups;
vector<int> id;

void solve(int n, int q, vector<int> arr, vector<pii> qs) {
  id.resize(n); fill(id.begin(), id.end(), -1);
  sort(qs.begin(), qs.end());
  int mend = qs[0].second;
  for (int i = 1; i < q; ++i) {
    if (qs[i].first != qs[i - 1].first) larg.insert({qs[i - 1].first, mend});
    mend = max(mend, qs[i].second);
  }
  larg.insert({qs[q - 1].first, mend});
  int cl = 0, cr = 0;
  set<pii> cur; cur.insert({arr[0], 0});
  for (int i = 0; i < q; ++i) {
    while (cl < min(qs[i].first, cr)) cur.erase({arr[cl], cl++});
    while (cr < qs[i].first) cur.erase({arr[cl], cl++}), cur.insert({arr[++cr], cr});
    while (cr < qs[i].second) {
      ++cr;
      auto it = cur.lower_bound({arr[cr], 0});
      if (it != cur.end() && it->first == arr[cr]) {
        if (id[it->second] < 0) id[it->second] = groups.size(), groups.push_back(vector<int>()), groups[id[it->second]].push_back(it->second);
        id[cr] = id[it->second], groups[id[cr]].push_back(cr);
      }
      cur.insert({arr[cr], cr});
    }
  }
}

int getMin(vector<pair<pii, pii>> ch) {
  sort(ch.begin(), ch.end());
  set<pii> mho, mht, chb; for (int i = 0; i < ch.size(); ++i) chb.insert({min(ch[i].first.second, ch[i].second.second), i});
  set<pii> a, b, c; for (int i = 0; i < ch.size(); ++i) c.insert({ch[i].second.first, i});
  int ans = INT_MAX;
  for (int i = 0; i < ch.size(); ++i) {
    int comp = ch[i].first.second;
    while (c.size()) {
      int ind = c.begin()->second;
      if (ch[ind].second.first < ch[i].first.first)
        mht.insert({ch[ind].first.second, ind}), chb.erase({min(ch[ind].first.second, ch[ind].second.second), i}),
          b.insert({ch[ind].first.first, ind}), c.erase(c.begin());
      else break;
    }
    while (a.size()) {
      int ind = a.begin()->second;
      if (ch[ind].second.first < ch[i].first.first) return ans;
      else break;
    }
    if (mho.size()) comp = max(comp, (--mho.end())->first);
    if (mht.size()) comp = max(comp, (--mht.end())->first);
    if (chb.size()) comp = max(comp, (--chb.end())->first);
    ans = min(ans, comp - ch[i].first.first + 1);
    mho.insert({ch[i].second.second, i});
    mht.erase({ch[i].first.second, i});
    chb.erase({min(ch[i].first.second, ch[i].second.second), i});
    a.insert({ch[i].second.first, i});
    b.erase({ch[i].first.first, i});
    c.erase({ch[i].second.first, i});
  }
  return ans;
}

void solve() {
  larg.clear();
  groups.clear();
  id.clear();
  int n, q; cin >> n >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<pii> qs(q); for (int i = 0; i < q; ++i) cin >> qs[i].first >> qs[i].second;
  for (int i = 0; i < q; ++i) --qs[i].first, --qs[i].second;
  solve(n, q, arr, qs);
  if (!groups.size()) {
    cout << 0 << '\n';
    return;
  }
  vector<pair<pii, pii>> ch(groups.size());
  for (int i = 0; i < groups.size(); ++i) {
    vector<int> group = groups[i];
    pii val = *--larg.upper_bound({group[0], INT_MAX});
    if (val.second >= group[group.size() - 1]) ch[i] = {{group[0], group[group.size() - 2]}, {group[1], group[group.size() - 1]}};
    else ch[i] = {{group[1], group[group.size() - 2]}, {group[1], group[group.size() - 2]}};
  }
  int ans = getMin(ch);
  for (int i = 0; i < ch.size(); ++i) swap(ch[i].first, ch[i].second);
  cout << min(ans, getMin(ch)) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

