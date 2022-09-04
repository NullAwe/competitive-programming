#include <bits/stdc++.h>
using namespace std;

#define ll __int128
#define pii pair<int, int>

struct F {

  __int128 num, dem;

  F() : num(0), dem(1) {}

  F(ll num, ll dem) : num(num), dem(dem) {}

  inline ll GCD(ll a, ll b) {
    while (b) a %= b, swap(a, b);
    return a;
  }

  inline ll abs(ll a) {
    return a >= 0 ? a : -a;
  }

  inline F operator+(int f) {
    ll n = num + f * dem, d = dem, g = GCD(abs(n), d);
    return F(n / g, d / g);
  }

  inline F operator+(F f) {
    ll n = num * f.dem + f.num * dem, d = dem * f.dem, g = GCD(abs(n), d);
    return F(n / g, d / g);
  }

  inline F operator-(F f) {
    ll n = num * f.dem - f.num * dem, d = dem * f.dem, g = GCD(abs(n), d);
    return F(n / g, d / g);
  }

  inline F operator*(int f) {
    ll n = num * f, d = dem, g = GCD(abs(n), d);
    return F(n / g, d / g);
  }

  inline F operator*(F f) {
    ll n = num * f.num, d = dem * f.dem, g = GCD(abs(n), d);
    return F(n / g, d / g);
  }

  inline F operator/(F f) {
    ll n = num * f.dem, d = dem * f.num, g = GCD(abs(n), abs(d));
    if (n < 0 && d < 0) n *= -1, d *= -1;
    return F(n / g, d / g);
  }

  inline bool operator==(F f) {
    return num == f.num && dem == f.dem;
  }

  inline bool operator<(F f) {
    return num * f.dem < f.num * dem;
  }

  inline bool operator>(F f) {
    return num * f.dem > f.num * dem;
  }
};

F LAST = F(2e9, 1);

vector<pair<F, F>> mn, mx;
vector<F> ans;

inline void imn(pii line) {
  F second = LAST * (-line.second) + line.first;
  if (!mn.size()) {
    mn.push_back({LAST, second}), mn.push_back({F(0, 1), F(line.first, 1)});
    return;
  }
  int lo = -1, hi = mn.size();
  while (lo < hi - 1) {
    int mid = (lo + hi) >> 1;
    F t = mn[mid].first, v = mn[mid].second;
    second = t * (-line.second) + line.first;
    if (second > v) lo = mid;
    else hi = mid;
  }
  F t = LAST;
  if (lo >= 0) {
    F x1 = mn[hi].first, y1 = mn[hi].second, x2 = mn[lo].first, y2 = mn[lo].second;
    F m1 = (y2 - y1) / (x2 - x1), b1 = y1 - m1 * x1, m2 = F(-line.second, 1), b2 = F(line.first, 1);
    t = (b2 - b1) / (m1 - m2);
  }
  mn.resize(hi);
  second = t * (-line.second) + line.first;
  mn.push_back({t, second}), mn.push_back({F(0, 1), F(line.first, 1)});
}

inline void imx(pii line) {
  F second = LAST * (-line.second) + line.first;
  if (!mx.size()) {
    mx.push_back({LAST, second}), mx.push_back({F(0, 1), F(line.first, 1)});
    return;
  }
  int lo = -1, hi = mx.size();
  while (lo < hi - 1) {
    int mid = (lo + hi) >> 1;
    F t = mx[mid].first, v = mx[mid].second;
    second = t * (-line.second) + line.first;
    if (second < v) lo = mid;
    else hi = mid;
  }
  F t = LAST;
  if (lo >= 0) {
    F x1 = mx[hi].first, y1 = mx[hi].second, x2 = mx[lo].first, y2 = mx[lo].second;
    F m1 = (y2 - y1) / (x2 - x1), b1 = y1 - m1 * x1, m2 = F(-line.second, 1), b2 = F(line.first, 1);
    t = (b2 - b1) / (m1 - m2);
  }
  mx.resize(hi);
  second = t * (-line.second) + line.first;
  mx.push_back({t, second}), mx.push_back({F(0, 1), F(line.first, 1)});
}

inline F amn(pii line) {
  int lo = -1, hi = mn.size();
  while (lo < hi - 1) {
    int mid = (lo + hi) >> 1;
    F t = mn[mid].first, v = mn[mid].second;
    F second = t * (-line.second) + line.first;
    if (second > v) lo = mid;
    else hi = mid;
  }
  F t = LAST;
  if (lo >= 0) {
    F x1 = mn[hi].first, y1 = mn[hi].second, x2 = mn[lo].first, y2 = mn[lo].second;
    F m1 = (y2 - y1) / (x2 - x1), b1 = y1 - m1 * x1, m2 = F(-line.second, 1), b2 = F(line.first, 1);
    t = (b2 - b1) / (m1 - m2);
  }
  return lo < 0 ? F(-1, 1) : t;
}

inline F amx(pii line) {
  F second = LAST * (-line.second) + line.first;
  int lo = -1, hi = mx.size();
  while (lo < hi - 1) {
    int mid = (lo + hi) >> 1;
    F t = mx[mid].first, v = mx[mid].second;
    second = t * (-line.second) + line.first;
    if (second < v) lo = mid;
    else hi = mid;
  }
  F t = LAST;
  if (lo >= 0) {
    F x1 = mx[hi].first, y1 = mx[hi].second, x2 = mx[lo].first, y2 = mx[lo].second;
    F m1 = (y2 - y1) / (x2 - x1), b1 = y1 - m1 * x1, m2 = F(-line.second, 1), b2 = F(line.first, 1);
    t = (b2 - b1) / (m1 - m2);
  }
  return lo < 0 ? F(-1, 1) : t;
}

int main() {
  ifstream in("falling.in");
  ofstream out("falling.out");
  int n; in >> n;
  ans.resize(n), mn.reserve(n), mx.reserve(n);
  vector<pii> arr(n); for (int i = 0; i < n; ++i) in >> arr[i].first;
  for (int i = 0; i < n; ++i) arr[i].second = i + 1;
  vector<pii> copy = arr;
  vector<int> qs(n); for (int i = 0; i < n; ++i) in >> qs[i];
  for (int i = 0; i < n; ++i) --qs[i];
  sort(copy.begin(), copy.end());
  for (pii p : copy) {
    imx(p);
    if (arr[qs[p.second - 1]].first > p.first) ans[p.second - 1] = amx(arr[qs[p.second - 1]]);
  }
  reverse(copy.begin(), copy.end());
  for (pii p : copy) {
    imn(p);
    if (arr[qs[p.second - 1]].first < p.first) ans[p.second - 1] = amn(arr[qs[p.second - 1]]);
  }
  for (F num : ans) {
    if (num.num < 0) out << -1 << '\n';
    else out << (long long) num.num << '/' << (long long) num.dem << '\n';
  }
  return 0;
}
