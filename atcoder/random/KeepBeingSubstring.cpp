#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int MAX_N = 200001;
const int ALPHA = MAX_N + 2;
const int INF = 1000000000;
const int LOG = 18;

struct suffix_lcs {

  int n, m;
  vector<int> arr, suffix;
  vector<vector<int>> cs;

  suffix_lcs() {}

  suffix_lcs(int n, int m, vector<int> a, vector<int> b) : n(n), m(m), arr(n + m + 2) {
    for (int i = 0; i < n; ++i) arr[i] = a[i];
    arr[n] = MAX_N;
    for (int i = 0; i < m; ++i) arr[i + n + 1] = b[i];
    arr[n + m + 1] = MAX_N + 1;
  }

  void build() {
    int N = arr.size();
    vector<int> p(N), c(N), cnt(max(ALPHA, N));
    for (int num : arr) ++cnt[num];
    for (int i = 1; i < ALPHA; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < N; ++i) p[--cnt[arr[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < N; ++i) {
      if (arr[p[i]] != arr[p[i - 1]]) ++classes;
      c[p[i]] = classes - 1;
    }
    vector<int> pn(N), cn(N);
    for (int h = 0; (1 << h) < N; ++h) {
      cs.push_back(c);
      for (int i = 0; i < N; ++i) {
        pn[i] = p[i] - (1 << h);
        if (pn[i] < 0) pn[i] += N;
      }
      fill(cnt.begin(), cnt.begin() + classes, 0);
      for (int i = 0; i < N; ++i) ++cnt[c[pn[i]]];
      for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
      for (int i = N - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];
      cn[p[0]] = 0;
      classes = 1;
      for (int i = 1; i < N; ++i) {
        pii cur = {c[p[i]], c[(p[i] + (1 << h)) % N]};
        pii prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % N]};
        if (cur != prev) ++classes;
        cn[p[i]] = classes - 1;
      }
      swap(c, cn);
    }
    suffix = p;
  }

  int lcp(int i, int j) {
    int ans = 0;
    i = suffix[i], j = suffix[j];
    for (int k = LOG - 1; k >= 0; --k) {
      if (k >= cs.size()) continue;
      if (cs[k][i % (n + m + 2)] == cs[k][j % (n + m + 2)]) {
        ans += (1 << k);
        i += (1 << k);
        j += (1 << k);
      }
    }
    return ans;
  }

  int lcs() {
    int la = -1, lb = -1, ans = 0;
    for (int i = 0; i < n + m + 2; ++i) {
      if (suffix[i] < n) la = i;
      else if (suffix[i] <= n + m && suffix[i] > n) lb = i;
      if (la >= 0 && lb >= 0) ans = max(ans, lcp(la, lb));
    }
    return ans;
  }
};

struct array_graph {

  vector<int> adj[MAX_N];
  int dist[MAX_N];

  array_graph() {}

  void add(vector<int>& arr) {
    for (int i = 0; i < MAX_N; ++i) dist[i] = INF;
    for (int i = 1; i < arr.size(); ++i) {
      adj[arr[i]].push_back(arr[i - 1]);
      adj[arr[i - 1]].push_back(arr[i]);
    }
  }

  void search(vector<int>& a) {
    queue<int> q;
    for (int v : a) if (dist[v] == INF) dist[v] = 0, q.push(v);
    while (q.size()) {
      int v = q.front(); q.pop();
      for (int u : adj[v]) {
        if (dist[u] < INF) continue;
        dist[u] = dist[v] + 1, q.push(u);
      }
    }
  }

  int find(vector<int>& b) {
    int ans = INF;
    for (int v : b) ans = min(ans, dist[v]);
    return ans;
  }
};

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int x; cin >> x;
  vector<int> a(x); for (int i = 0; i < x; ++i) cin >> a[i];
  int y; cin >> y;
  vector<int> b(y); for (int i = 0; i < y; ++i) cin >> b[i];
  suffix_lcs suffix(x, y, a, b); suffix.build();
  array_graph gr; gr.add(arr); gr.search(a);
  cout << (x + y - 2 * suffix.lcs() + 2 * max(gr.find(b) - 1, 0)) << '\n';
  return 0;
}