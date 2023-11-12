#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

int n, q;
vector<pair<pii, pii>> qrys;
vector<pii> qs;
set<pii> can;

struct Segtree {

  int n;
  vector<int> t;

  Segtree() {}

  Segtree(int n) : n(n), t(2 * n) {}

  void inc(int p, int v) {
    for (t[p += n] += v; p > 1; p >>= 1) t[p >> 1] += v;
  }

  int qry(int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans += t[l++];
      if (r & 1) ans += t[--r];
    }
    return ans;
  }
};

void init(vector<int>& arr, vector<int>& back) {
  vector<pii> rngs(n, {-1, -1});
  set<pii> sorted;
  sorted.insert({n, n});
  for (int k = 0; k < n; ++k) {
    int i = back[k];
    bool ml = i > 0 && rngs[i - 1].second >= 0, mr = i < n - 1 && rngs[i + 1].second >= 0;
    if (ml && mr) {
      sorted.erase(rngs[i - 1]), sorted.erase(rngs[i + 1]);
      rngs[rngs[i - 1].first].second = rngs[i + 1].second;
      rngs[rngs[i + 1].second].first = rngs[i - 1].first;
      sorted.insert(rngs[rngs[i - 1].first]);
      rngs[i] = rngs[rngs[i - 1].first];
    } else if (ml) {
      sorted.erase(rngs[i - 1]);
      rngs[rngs[i - 1].first].second = i;
      rngs[i] = {rngs[i - 1].first, i};
      sorted.insert(rngs[rngs[i - 1].first]);
    } else if (mr) {
      sorted.erase(rngs[i + 1]);
      rngs[rngs[i + 1].second].first = i;
      rngs[i] = {i, rngs[i + 1].second};
      sorted.insert(rngs[rngs[i + 1].second]);
    } else {
      sorted.insert(rngs[i] = {i, i});
    }
    int pl = rngs[i].first, pr = rngs[i].second;
    pii next = *sorted.lower_bound({pr + 1, pr + 1});
    int ppl = pr + 1, ppr = sorted.lower_bound({pr + 1, pr + 1})->first - 1;
    qrys.push_back({{pl, pr}, {ppl, ppr}});
  }
}

void process() {
  Segtree st(n + 1);
  vector<vector<pii>> begins(n), ends(n);
  for (auto qry : qrys) {
    begins[qry.first.first].push_back(qry.second);
    ends[qry.first.second].push_back(qry.second);
  }
  vector<vector<int>> qqs(n);
  for (pii qq : qs) qqs[qq.first].push_back(qq.second);
  for (int i = 0; i < n; ++i) {
    for (pii p : begins[i]) {
      st.inc(p.first, 1);
      st.inc(p.second + 1, -1);
    }
    for (int y : qqs[i]) if (st.qry(0, y + 1) > 0) can.insert({i, y});
    for (pii p : ends[i]) {
      st.inc(p.first, -1);
      st.inc(p.second + 1, 1);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> back(n); for (int i = 0; i < n; ++i) back[arr[i] - 1] = i;
  init(arr, back);
  cin >> q; qs.resize(q);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    qs[i] = {a, b};
  }
  process();
  for (pii pp : qs) {
    if (can.count(pp)) cout << "Yes\n";
    else cout << "No\n";
  }
}