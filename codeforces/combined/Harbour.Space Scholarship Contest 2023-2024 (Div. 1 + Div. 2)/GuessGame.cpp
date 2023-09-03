#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

inline ll p(ll x, ll y) {
  x %= MOD;
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD;
    y >>= 1;
  }
  return ans;
}

inline ll inv(ll x) {
  return p(x, MOD - 2);
}

static char buf[240 << 20];
void* operator new(size_t s) {
	static size_t i = sizeof buf;
	assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) {}

struct magic_struct {

  vector<magic_struct*> children;
  int at, c;

  magic_struct(int at) : children(2, nullptr), at(at), c(0) {}

  void insert(int x) {
    ++c;
    if (at == -1) return;
    if (children[(x >> at) & 1] == nullptr) children[(x >> at) & 1] = new magic_struct(at - 1);
    children[(x >> at) & 1]->insert(x - (x & (1 << at)));
  }

  int cnt(int x, int shift) {
    if (at == shift - 1) return c;
    int child = (x >> at) & 1;
    if (children[child] == nullptr) return 0;
    return children[child]->cnt(x, shift);
  }
};

inline void solve() {
  int n; cin >> n;
  ll ans = 0;
  magic_struct magical(29);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    ans += (__builtin_popcount(x) + 1) * (2 * magical.cnt(x, 0) + 1);
    int tmp = x, left = i - magical.cnt(x, 0);
    for (int j = 0; j < 30 && tmp > 0; ++j) {
      tmp ^= (1 << j);
      left -= magical.cnt(tmp, j);
      ans = (ans + (2 * __builtin_popcount(tmp - (tmp & (1 << j))) + 3) * magical.cnt(tmp, j)) % MOD;
      tmp -= (tmp & (1 << j));
    }
    ans = (ans + 3 * left) % MOD;
    magical.insert(x);
  }
  cout << (ans * inv((ll) n * n % MOD)) % MOD << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
