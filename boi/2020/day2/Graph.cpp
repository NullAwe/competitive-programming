#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const double EPS = 0.000001;

struct line {

  int m, b;

  line() {}

  line(int m, int b) : m(m), b(b) {}

  double combine(line other) {
    int mm = m - other.m, bb = other.b - b;
    if (mm == 0 && bb) {
      cout << "NO\n";
      exit(0);
    }
    if (mm == 0) return INT_MAX;
    return (double) bb / mm;
  }
};

int n, m;
vector<vector<pii>> adj;
vector<line> lines;
vector<bool> vis;
vector<double> all;

void solve(int fv) {
  if (vis[fv]) return;
  lines[fv] = line(1, 0);
  queue<int> q;
  vector<int> has;
  vis[fv] = true, q.push(fv), has.push_back(fv);
  double ans = INT_MAX;
  while (q.size()) {
    int v = q.front(); q.pop();
    for (pii p : adj[v]) {
      int u = p.first, c = p.second;
      line change(-lines[v].m, c - lines[v].b);
      if (!vis[u]) {
        vis[u] = true, q.push(u), has.push_back(u);
        lines[u] = change;
      } else {
        double comb = lines[u].combine(change);
        if (ans > INT_MAX - 1) ans = comb;
      }
    }
  }
  if (ans > INT_MAX - 1) {
    vector<pii> values;
    vector<int> orig;
    int ind = 0;
    for (int v : has) {
      line l = lines[v];
      values.push_back({-l.b / l.m, ind++});
      orig.push_back(-l.b / l.m);
    }
    vector<pii> negs(values.size());
    for (int i = 0; i < values.size(); ++i) negs[i] = {-values[i].first, i};
    sort(values.begin(), values.end());
    sort(negs.begin(), negs.end());
    vector<ll> arr(values.size());
    vector<int> pos, neg;
    for (int v : has) {
      line l = lines[v];
      if (l.m > 0) pos.push_back(-l.b);
      else neg.push_back(-l.b);
    }
    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end());
    vector<ll> pp(pos.size() + 1), pn(neg.size() + 1);
    for (int i = 0; i < pos.size(); ++i) pp[i + 1] = pp[i] - pos[i];
    for (int i = 0; i < neg.size(); ++i) pn[i + 1] = pn[i] - neg[i];
    int pi = 0, ni = 0;
    for (pii p : values) {
      int num = p.first;
      while (pi < pos.size() && pos[pi] < num) ++pi;
      arr[p.second] = pp[pi] + (ll) num * pi - (pp[(int) pos.size()] - pp[pi]) - (ll) num * ((int) pos.size() - pi);
    }
    for (pii p : negs) {
      int num = p.first;
      while (ni < neg.size() && neg[ni] < num) ++ni;
      arr[p.second] += pn[ni] + (ll) num * ni - (pn[(int) neg.size()] - pn[ni]) - (ll) num * ((int) neg.size() - ni);
    }
    ll mn = LLONG_MAX;
    for (int i = 0; i < values.size(); ++i) {
      if (arr[i] < mn) mn = arr[i], ans = orig[i];
    }
  }
  for (int v : has) vis[v] = false;
  all[fv] = ans;
  q = queue<int>();
  vis[fv] = true, q.push(fv);
  while (q.size()) {
    int v = q.front(); q.pop();
    for (pii p : adj[v]) {
      int u = p.first, c = p.second;
      if (vis[u]) continue;
      vis[u] = true, q.push(u);
      all[u] = c - all[v];
    }
  }
}

int main() {
  cin >> n >> m;
  adj.resize(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c; cin >> a >> b >> c; --a, --b;
    adj[a].push_back({b, c}), adj[b].push_back({a, c});
  }
  lines = vector<line>(n);
  vis = vector<bool>(n);
  all.resize(n);
  for (int i = 0; i < n; ++i) solve(i);
  for (int v = 0; v < n; ++v) {
    for (pii p : adj[v]) {
      if (abs(all[v] + all[p.first] - p.second) > EPS) {
        cout << "NO\n";
        return 0;
      }
    }
  }
  cout << "YES\n";
  for (double val : all) cout << val << ' ';
  cout << '\n';
  return 0;
}
