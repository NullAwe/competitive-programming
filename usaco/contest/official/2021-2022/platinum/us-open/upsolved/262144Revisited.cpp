#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

int n;
vector<int> r, p, v;
vector<pii> rng;

int find(int a) {
  return p[a] == a ? a : p[a] = find(p[a]);
}

bool link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return false;
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
  return true;
}

bool mr(int a) {
  a = find(a);
  if (rng[a].second + 1 >= n) return false;
  int b = find(rng[a].second + 1);
  if (v[a] != v[b]) return false;
  link(a, b);
  int c = find(a);
  v[c] = v[b], rng[c] = {rng[a].first, rng[b].second};
  return true;
}

void upd(int a, int b) {
  v[find(a)] = b;
}

int qry(int a) {
  return v[find(a)];
}

pii qryrng(int a) {
  return rng[find(a)];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int mx = 0; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int num : arr) mx = max(mx, num);
  r.resize(n + 1), p.resize(n + 1), v.resize(n + 1), rng.resize(n + 1);
  for (int i = 0; i <= n; ++i) p[i] = i, rng[i] = {i, i};
  upd(n, n);
  vector<vector<int>> in(mx + 1), acc(n + 1); for (int i = 0; i < n; ++i) in[arr[i]].push_back(i);
  for (int i : in[1]) upd(i, i + 1), acc[i + 1].push_back(i);
  ll ans = in[1].size(), mult = 1;
  vector<int> todo;
  for (int i = 1; i < n; ++i) if (qry(i)) for (int from : acc[i]) todo.push_back(from);
  while (++mult) {
    if (mult > mx && !todo.size()) break;
    vector<int> ntodo;
    for (int i : in[mult]) {
      upd(i, i + 1), ans += mult;
      for (int from : acc[i]) ntodo.push_back(from);
      if (i < n - 1 && qry(i + 1)) ntodo.push_back(i);
      else if (i != n - 1) acc[i + 1].push_back(i);
    }
    for (int i : todo) {
      int store = qry(i), nt = qry(store);
      pii srng = qryrng(i);
      ans += mult * (nt - store) * (srng.second - srng.first + 1);
      if (nt < n && qry(nt)) ntodo.push_back(i);
      else if (nt != n) acc[nt].push_back(i);
      upd(i, nt);
    }
    for (int i : todo) while (mr(i));
    todo.clear();
    sort(ntodo.begin(), ntodo.end());
    for (int i : ntodo) {
      int root = find(i);
      if (!todo.size() || todo.back() != root) todo.push_back(root);
    }
  }
  cout << ans << '\n';
  return 0;
}
