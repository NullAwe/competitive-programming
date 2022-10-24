#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>

#define sq(x) ((x) * (x))

const int MAX_N = 200001;

struct pt {
  ll x, y;
};

inline int orient(pt a, pt b, pt c) {
  ll v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
  return v < 0 ? -1 : v > 0;
}

inline void convex(vector<pt>& a) {
  pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) { return a.y < b.y || (a.y == b.y && a.x < b.x); });
  sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
    int o = orient(p0, a, b);
    if (o == 0) return sq(p0.x - a.x) + sq(p0.y - a.y) < sq(p0.x - b.x) + sq(p0.y - b.y);
    return o < 0;
  });
  vector<pt> ch;
  for (int i = 0; i < a.size(); ++i) {
    while (ch.size() > 1 && orient(ch[ch.size() - 2], ch.back(), a[i]) >= 0) ch.resize(ch.size() - 1);
    ch.push_back(a[i]);
  }
  a = ch;
}

vector<pt> sides;

void add(vector<pt>& a) {
  convex(a), a.push_back(a[0]);
  for (int i = 1; i < a.size(); ++i) {
    pt p; p.x = a[i].x - a[i - 1].x, p.y = a[i].y - a[i - 1].y;
    sides.push_back(p);
  }
}

int main() {
  int groups; cin >> groups;
  vector<pt> a;
  pt tr;
  for (int group = 0; group < groups; ++group) {
    int n; cin >> n; a.resize(n);
    for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y;
    add(a);
    pt ch; ch.x = INT_MIN;
    for (pt p : a) if (p.x > ch.x || (p.x == ch.x && p.y > ch.y)) ch = p;
    tr.x += ch.x, tr.y += ch.y;
  }
  sort(sides.begin(), sides.end(), [](const pt& a, const pt& b) {
    if (!b.x && b.y < 0) return false;
    if (!a.x && a.y < 0) return true;
    if (!a.x) return b.x > 0;
    if (a.x < 0 != b.x < 0) return a.x < b.x;
    return orient(pt(), a, b) == -1;
  });
  ll ans = 0;
  for (pt p : sides) {
    tr.x += p.x, tr.y += p.y;
    ans = max(ans, sq(tr.x) + sq(tr.y));
  }
  cout << ans << '\n';
  return 0;
}
