#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_N = 250;
const ll N_INF = LLONG_MIN >> 2;

ll ans[MAX_N];

struct matr {

  ll m[MAX_N][MAX_N];

  matr() {
    for (int i = 0; i < MAX_N; ++i) for (int j = 0; j < MAX_N; ++j) m[i][j] = N_INF;
  }

  inline void join() {
    ll nans[MAX_N]; for (int i = 0; i < MAX_N; ++i) nans[i] = N_INF;
    for (int i = 0; i < MAX_N; ++i) {
      for (int j = 0; j < MAX_N; ++j) {
        ll sum = ans[i] + m[i][j];
        if (sum >= 0) nans[j] = max(nans[j], sum);
      }
    }
    for (int i = 0; i < MAX_N; ++i) ans[i] = nans[i];
  }

  inline matr join(matr b) {
    matr nans;
    for (int i = 0; i < MAX_N; ++i) {
      for (int j = 0; j < MAX_N; ++j) {
        for (int k = 0; k < MAX_N; ++k) {
          ll sum = m[i][k] + b.m[k][j];
          if (sum >= 0) nans.m[i][j] = max(nans.m[i][j], sum);
        }
      }
    }
    return nans;
  }
};

matr adj[30];

inline void p(int b) {
  for (int i = 0; i < 30; ++i) if (b & (1 << i)) adj[i].join();
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m, t, k; cin >> n >> m >> t >> k;
  int arr[n]; for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    int lst = a;
    for (int j = 1; j < w; ++j) adj[0].m[lst][(5 - w + j) * n + b] = 0, lst = (5 - w + j) * n + b;
    adj[0].m[lst][b] = arr[b];
  }
  for (int i = 1; i < 30; ++i) adj[i] = adj[i - 1].join(adj[i - 1]);
  pair<int, pair<int, int>> fs[k];
  for (int i = 0; i < k; ++i) cin >> fs[i].first >> fs[i].second.first >> fs[i].second.second;
  sort(fs, fs + k);
  ans[0] = arr[0];
  for (int i = 1; i < MAX_N; ++i) ans[i] = N_INF;
  int ct = 0;
  for (auto f : fs) {
    p(f.first - ct), ct = f.first;
    if (ans[f.second.first - 1] >= 0) ans[f.second.first - 1] += f.second.second;
  }
  p(t - ct);
  cout << (ans[0] < 0 ? -1 : ans[0]) << '\n';
  return 0;
}
