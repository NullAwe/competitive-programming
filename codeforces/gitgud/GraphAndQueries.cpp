#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> t, arr, r, p;

inline int find(int a) {
  return a == p[a] ? a : p[a] = find(p[a]);
}

inline void link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return;
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
}

inline int bld(int v, int l, int r) {
  if (l == r) return t[v] = arr[l];
  int m = (l + r) / 2;
  return t[v] = max(bld(v << 1, l, m), bld((v << 1) + 1, m + 1, r));
}

inline void rem(int v, int tl, int tr, int p) {
  if (tl == tr) t[v] = 0;
  else {
    int m = (tl + tr) / 2;
    if (p <= m) rem(v << 1, tl, m, p);
    else rem((v << 1) + 1, m + 1, tr, p);
    t[v] = max(t[v << 1], t[(v << 1) + 1]);
  }
}

inline int qry(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (tl == l && tr == r) return t[v];
  int m = (tl + tr) / 2;
  return max(qry(v << 1, tl, m, l, min(m, r)), qry((v << 1) + 1, m + 1, tr, max(m + 1, l), r));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m, q; cin >> n >> m >> q;
  vector<int> perm(n); for (int i = 0; i < n; ++i) cin >> perm[i], --perm[i];
  vector<vector<pii>> adj(n);
  vector<pii> edges(m);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
    edges[i] = {a, b};
  }
  vector<pii> qs(q);
  for (int i = 0; i < q; ++i) cin >> qs[i].first >> qs[i].second;
  for (int i = 0; i < q; ++i) --qs[i].second;
  vector<bool> off(m);
  int t2 = 0;
  for (pii query : qs) if (query.first == 2) ++t2, off[query.second] = true;
  r.resize(n), p.resize(n); for (int i = 0; i < n; ++i) p[i] = i;
  vector<bool> vis(n);
  for (int i = 0; i < n; ++i) {
    if (vis[i]) continue;
    vis[i] = true;
    queue<int> q; q.push(i);
    while (q.size()) {
      int v = q.front(); q.pop();
      for (pii u : adj[v]) {
        if (vis[u.first] || off[u.second]) continue;
        vis[u.first] = true;
        q.push(u.first);
        link(i, u.first);
      }
    }
  }
  vector<int> cp = p;
  vector<vector<int>> actual(n);
  vector<bool> fin(n);
  for (int i = 0; i < n; ++i) {
    int pi = find(i);
    if (!actual[pi].size()) actual[pi].push_back(pi), fin[pi] = true;
  }
  vector<vector<int>*> tracker(n);
  for (int i = 0; i < n; ++i) tracker[i] = &actual[i];
  vector<pii> splits;
  for (int i = q - 1; i >= 0; --i) {
    if (qs[i].first == 1) continue;
    int a = edges[qs[i].second].first, b = edges[qs[i].second].second;
    a = find(a), b = find(b);
    if (a == b) {
      splits.push_back({-1, -1});
      continue;
    }
    fin[a] = fin[b] = false;
    if (tracker[a]->size() < tracker[b]->size()) swap(tracker[a], tracker[b]);
    splits.push_back({tracker[a]->back(), tracker[b]->front()});
    for (int num : *tracker[b]) tracker[a]->push_back(num);
    link(a, b);
    b = find(b);
    tracker[b] = tracker[a];
    fin[b] = true;
  }
  vector<int> order;
  for (int i = 0; i < n; ++i) if (fin[i]) for (int num : *tracker[i]) order.push_back(num);
  p = cp;
  map<int, int> ids; for (int i = 0; i < order.size(); ++i) ids[order[i]] = i;
  vector<int> np(n);
  for (int i = 0; i < n; ++i) np[i] = ids[find(p[i])];
  p = np;
  for (int i = 0; i < splits.size(); ++i) splits[i].first = ids[splits[i].first], splits[i].second = ids[splits[i].second];
  vector<pii> nums(n); for (int i = 0; i < n; ++i) nums[i] = {p[i], perm[i]};
  sort(nums.begin(), nums.end());
  vector<int> back(n); for (int i = 0; i < n; ++i) back[nums[i].second] = i;
  t.resize(4 * n);
  vector<int> begin(order.size(), -1);
  set<int> starts;
  for (int i = 0; i < n; ++i) {
    arr.push_back(nums[i].second + 1);
    if (begin[nums[i].first] < 0) begin[nums[i].first] = i, starts.insert(i);
  }
  bld(1, 0, n - 1);
  starts.insert(n);
  for (pii split : splits) if (split.second) starts.erase(begin[split.second]);
  reverse(splits.begin(), splits.end()); int ind = 0;
  for (pii query : qs) {
    if (query.first == 1) {
      auto up = starts.upper_bound(back[perm[query.second]]);
      int r = *up, l = *--up;
      int ans = qry(1, 0, n - 1, l, r - 1);
      cout << ans << '\n';
      if (ans == 0) continue;
      rem(1, 0, n - 1, back[ans - 1]);
    } else if (splits[ind].second) starts.insert(begin[splits[ind++].second]);
    else ++ind;
  }
  return 0;
}
