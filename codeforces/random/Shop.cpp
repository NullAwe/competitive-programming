#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<ll> arr, track;

struct upg {

  int type, ind, amount, pos;
  ll num, dem;

  upg(int type, int ind, int amount, int pos) : type(type), ind(ind), amount(amount), pos(pos), num(0), dem(1) {}

  void rate() {
    if (type == 2) num = amount;
    else dem = track[ind], num = dem + (type ? amount : amount - arr[ind]), track[ind] = num;
  }

  bool operator<(const upg& other) const {
    if ((__int128) num * other.dem != (__int128) other.num * dem) return (__int128) num * other.dem > (__int128) other.num * dem;
    if ((type == 2) != (other.type == 2)) return type < other.type;
    int a = amount, b = other.amount;
    if (!type) a -= arr[ind];
    if (!other.type) b -= arr[other.ind];
    return a > b;
  }
};

int main() {
  int k, n, m; cin >> k >> n >> m;
  arr.resize(k); for (int i = 0; i < k; ++i) cin >> arr[i];
  track = arr;
  vector<pii> maxs(k);
  vector<upg> upgs;
  for (int i = 0; i < n; ++i) {
    int type, ind, amount; cin >> type >> ind >> amount; --type, --ind;
    if (!type) maxs[ind] = max(maxs[ind], {amount, i + 1});
    else upgs.push_back(upg(type, ind, amount, i + 1));
  }
  for (int i = 0; i < k; ++i) if (maxs[i].first > arr[i]) upgs.push_back(upg(0, i, maxs[i].first, maxs[i].second));
  n = upgs.size(), m = min(m, n);
  sort(upgs.begin(), upgs.end());
  for (int i = 0; i < n; ++i) upgs[i].rate();
  sort(upgs.begin(), upgs.end());
  vector<vector<pii>> buy(k);
  for (int i = 0; i < m; ++i) buy[upgs[i].ind].push_back({upgs[i].type, upgs[i].pos});
  cout << m << '\n';
  for (int i = 0; i < k; ++i) {
    sort(buy[i].begin(), buy[i].end());
    for (pii p : buy[i]) cout << p.second << ' ';
  }
  cout << '\n';
  return 0;
}

