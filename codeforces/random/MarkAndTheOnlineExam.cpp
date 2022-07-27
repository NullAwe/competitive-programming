#include <bits/stdc++.h>
using namespace std;

int n, queries;
vector<vector<int>> adj;
vector<int> r, p;

int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

void link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return;
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
}

int query(vector<int>& pos) {
  ++queries;
  while (queries == 675);
  string str(n, 'T');
  for (int i : pos) str[i] = 'F';
  printf("%s\n", str.c_str()); fflush(stdout);
  int res; scanf("%d", &res);
  if (res == n) exit(0);
  return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

int main() {
  cin >> n;
  queries = 0;
  adj.resize(n), r.resize(n), p.resize(n); for (int i = 0; i < n; ++i) p[i] = i;
  vector<int> type(n, -1);
  vector<int> rem(n); for (int i = 0; i < n; ++i) rem[i] = i;
  vector<int> fq;
  int norm = query(fq);
  while (rem.size()) {
    if (rem.size() & 1) {
      int first = rem.back(); rem.resize(rem.size() - 1);
      fq.clear(), fq.push_back(first);
      int res = query(fq);
      type[first] = res < norm;
      queue<int> q; q.push(first);
      while (q.size()) {
        int v = q.front(); q.pop();
        for (int u : adj[v]) {
          if (type[u] >= 0) continue;
          type[u] = 1 - type[v];
          q.push(u);
        }
      }
    }
    shuffle(rem.begin(), rem.end(), rng);
    vector<int> nrem;
    for (int i = 0; i < rem.size(); i += 2) {
      fq.clear(), fq.push_back(rem[i]), fq.push_back(rem[i + 1]);
      int res = query(fq);
      if (res == norm) {
        link(rem[i], rem[i + 1]);
        nrem.push_back(rem[i]);
        adj[rem[i]].push_back(rem[i + 1]);
        adj[rem[i + 1]].push_back(rem[i]);
      } else {
        type[rem[i]] = type[rem[i + 1]] = res < norm;
        queue<int> q; q.push(rem[i]), q.push(rem[i + 1]);
        while (q.size()) {
          int v = q.front(); q.pop();
          for (int u : adj[v]) {
            if (type[u] >= 0) continue;
            type[u] = 1 - type[v];
            q.push(u);
          }
        }
      }
    }
    rem = nrem;
  }
  for (int num : type) cout << (num ? 'T' : 'F');
  cout << '\n';
  return 0;
}
