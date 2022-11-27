#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

const int MAX_N = 400000;
bool s[MAX_N + 1][256];

ull myRand(ull &k1, ull &k2) {
  ull k3 = k1, k4 = k2;
  k1 = k4, k3 ^= (k3 << 23), k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
  return k2 + k4;
}

void gen(int n, ull a1, ull a2) {
  for (int i = 1; i <= n; i++) for (int j = 0; j < 256; j++)
    s[i][j] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  ull a1, a2; cin >> a1 >> a2;
  gen(n, a1, a2);
  int s2[n][16];
  for (int i = 0; i < n; ++i) for (int j = 0; j < 16; ++j) {
    s2[i][j] = 0;
    for (int k = 0; k < 16; ++k) s2[i][j] |= (s[i + 1][16 * j + k] << (15 - k));
  }
  vector<int> has[1 << 16][16];
  for (int i = 0; i < n; ++i) for (int j = 0; j < 16; ++j) has[s2[i][j]][j].push_back(i);
  int mp[200];
  for (int i = 0; i < 10; ++i) mp[i + '0'] = i;
  for (int i = 'A'; i < 'G'; ++i) mp[i] = i - 'A' + 10;
  int last = 0;
  for (int i = 0; i < m; ++i) {
    string str; cin >> str;
    int thresh; cin >> thresh;
    int vals[16];
    for (int j = 0; j < 16; ++j) {
      vals[j] = 0;
      for (int k = 0; k < 4; ++k) vals[j] |= (mp[str[4 * j + k]] << (4 * (3 - k)));
    }
    if (last) {
      for (int j = 0; j < 16; ++j) vals[j] ^= (1 << 16) - 1;
    }
    bool pos = false;
    for (int j = 0; j < 16; ++j) {
      if (pos) break;
      for (int num : has[vals[j]][j]) {
        int has = 0;
        for (int k = 0; k < 16; ++k) {
          has += __builtin_popcount(vals[k] ^ s2[num][k]);
          if (has > thresh) break;
        }
        if (has <= thresh) {
          pos = true;
          break;
        }
      }
    }
    cout << pos << '\n';
    last = pos;
  }
  return 0;
}
