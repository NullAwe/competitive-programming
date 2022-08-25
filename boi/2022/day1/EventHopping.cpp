#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int SZ = 20;

vector<vector<int>> tl;

// Segtree operations for maintaining reachable left nodes:
void btl(int n) {
  tl = vector<vector<int>>(2 * n, vector<int>(SZ));
  for (int i = 0; i < n; ++i) for (int j = 0; j < SZ; ++j) tl[i + n][j] = i;
  for (int i = n - 1; i > 0; --i) for (int j = 0; j < SZ; ++j) tl[i][j] = min(tl[2 * i][j], tl[2 * i + 1][j]);
}

void upd(int n, int p, int j, int v) { for (tl[p += n][j] = v; p > 1; p >>= 1) tl[p >> 1][j] = min(tl[p][j], tl[p ^ 1][j]); }

int qry(int n, int l, int r, int j) {
  int ans = INT_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = min(ans, tl[l++][j]);
    if (r & 1) ans = min(ans, tl[--r][j]);
  }
  return ans;
}

int main() {
  int n, q; cin >> n >> q;
  vector<pii> events(n); for (int i = 0; i < n; ++i) cin >> events[i].first >> events[i].second;
  set<int> nums; for (pii event : events) nums.insert(event.first), nums.insert(event.second);
  map<int, int> m;
  int id = 0;
  for (int num : nums) m[num] = id++;
  for (int i = 0; i < n; ++i) events[i].first = m[events[i].first], events[i].second = m[events[i].second];
  vector<int> mns(id); for (int i = 0; i < id; ++i) mns[i] = i;
  for (pii event : events) mns[event.second] = min(mns[event.second], event.first);
  vector<pii> qs(q); for (int i = 0; i < q; ++i) cin >> qs[i].first >> qs[i].second;
  for (int i = 0; i < q; ++i) --qs[i].first, --qs[i].second;
  vector<vector<pair<pii, int>>> fq(id);
  for (int i = 0; i < q; ++i) {
    if (qs[i].first == qs[i].second) continue;
    int e1 = events[qs[i].first].second, s2 = events[qs[i].second].first, e2 = events[qs[i].second].second;
    fq[e2].push_back({{s2, e1}, i});
  }
  btl(id);
  vector<vector<int>> jump(id, vector<int>(SZ));
  for (int i = 0; i < id; ++i) for (int j = 0; j < SZ; ++j) jump[i][j] = i;
  vector<int> ans(q);
  for (int i = 0; i < id; ++i) {
    // Updates jumps:
    upd(id, i, 0, mns[i]);
    for (int j = 1; j < SZ; ++j) upd(id, i, j, qry(id, tl[i + id][j - 1], id, j - 1));
    // Finds query answers:
    for (pair<pii, int> query : fq[i]) {
      int start = query.first.first, end = query.first.second, ind = query.second, count = 1;
      if (end > i) count = -1;
      while (start > end) {
        if (qry(id, start, i + 1, SZ - 1) > end) {
          count = -1;
          break;
        }
        int j = SZ - 1;
        for (; j >= 0; --j) {
          if (qry(id, start, i + 1, j) > end) {
            count += (1 << j);
            start = qry(id, start, i + 1, j);
            break;
          }
        }
        if (j < 0) ++count, start = qry(id, start, i + 1, 0);
      }
      ans[ind] = count;
    }
  }
  for (int num : ans) cout << (num < 0 ? "impossible" : to_string(num)) << '\n';
  return 0 ;
}
