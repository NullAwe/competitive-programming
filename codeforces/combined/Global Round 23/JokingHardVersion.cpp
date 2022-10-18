#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

struct IntervalSet {

  int sz = 0;
  vector<pii> s;

  IntervalSet() {}

  IntervalSet(int n) {
    sz = n, s.push_back({1, n});
  }

  void append(pii v) {
    sz += v.second - v.first + 1;
    if (s.empty()) s.push_back(v);
    else {
      if (v.first > s.back().second) {
        if (v.first == s.back().second + 1) s.back().second = v.second;
        else s.push_back(v);
      } else if (v.second > s.back().second) {
        sz -= s.back().second - v.first + 1;
        s.back().second = v.second;
      }
    }
  }

  pair<IntervalSet, IntervalSet> split(int k) {
    IntervalSet a, b;
    for (pii i : s) {
      if (i.second - i.first + 1 <= k) a.append(i), k -= i.second - i.first + 1;
      else if (k <= 0) b.append(i);
      else a.append({i.first, i.first + k - 1}), b.append({i.first + k, i.second}), k = 0;
    }
    return {a, b};
  }

  IntervalSet(const IntervalSet& x, const IntervalSet& y) {
    const vector<pii>& a = x.s;
    const vector<pii>& b = y.s;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
      if (a[i].first < b[j].first) append(a[i++]);
      else append(b[j++]);
    }
    while (i < a.size()) append(a[i++]);
    while (j < b.size()) append(b[j++]);
  }
};

const int MAX_SUM = 200;

pair<int, pii> k[MAX_SUM][MAX_SUM];
bool first = true;

pii getBest(int a, int b) {
  if (a + b >= MAX_SUM) return {a >> 1, b >> 1};
  if (first) {
    first = false;
    for (int sum = 0; sum < MAX_SUM; ++sum) for (int x = 0; x <= sum; ++x)
      k[x][sum - x] = {1000, {0, 0}};
    for (int sum = 0; sum < MAX_SUM; ++sum) {
      if (sum <= 2) for (int x = 0; x <= sum; ++x) k[x][sum - x] = {0, {0, 0}};
      else {
        bool rep = true;
        while (rep) {
          rep = false;
          for (int x = 0; x <= sum; ++x) {
            int y = sum - x;
            for (int x0 = 0; x0 <= x; ++x0) {
              for (int y0 = 0; y0 <= y; ++y0) {
                int x1 = x - x0, y1 = y - y0, x_ = x0 + y0, y_ = x1, x__ = x1 + y1, y__ = x0;
                int g = 1 + max(k[x_][y_].first, k[x__][y__].first);
                if (k[x][y].first > g) k[x][y] = {g, {x0, y0}}, rep = true;
              }
            }
          }
        }
      }
    }
  }
  return k[a][b].second;
}

int receive(int n, IntervalSet& a, IntervalSet& b, int a0, int b0) {
  vector<int> arr, done(n + 1); arr.reserve(n);
  for (pii iv : a.s) for (int i = iv.first; i <= iv.second; ++i) {
    if (a0) --a0;
    else if (!done[i]) arr.push_back(i), done[i] = 1;
  }
  for (pii iv : b.s) for (int i = iv.first; i <= iv.second; ++i) {
    if (b0) --b0;
    else if (!done[i]) arr.push_back(i), done[i] = 1;
  }
  printf("? %d", (int) arr.size());
  for (int num : arr) printf(" %d", num);
  printf("\n"); fflush(stdout);
  string res; cin >> res;
  return res == "YES" ? 1 : 0;
}

pii decode(int n) {
  IntervalSet a(n), b;
  while (a.sz + b.sz > 2) {
    pii c = getBest(a.sz, b.sz);
    int a0 = c.first, b0 = c.second;
    pair<IntervalSet, IntervalSet> a_ = a.split(a0), b_ = b.split(b0);
    int r = receive(n, a, b, a0, b0);
    if (!r) a = IntervalSet(a_.first, b_.first), b = a_.second;
    else a = IntervalSet(a_.second, b_.second), b = a_.first;
  }
  if (!a.sz) return {b.s[0].first, b.s.back().second};
  if (!b.sz) return {a.s[0].first, a.s.back().second};
  return {a.s[0].first, b.s[0].first};
}

void solve() {
  int n; cin >> n;
  pii guesses = decode(n);
  cout << "! " << guesses.first << endl;
  string res; cin >> res;
  if (res == ":)") return;
  else cout << "! " << guesses.second << endl;
  cin >> res;
}

int main() {
  solve();
  return 0;
}
