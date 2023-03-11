#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MAX_N = 300001;
const int LOG = 20;

const ll MOD = 1000000009;
const ll SMALL_P = 3;
const ll INV_P = 666666673;

string str;
vector<int> beg, ed;
set<int> rem;

ll hashes[MAX_N][LOG];
int nxt[MAX_N][LOG];
ll p3[MAX_N];

void collapse(int i) {
  hashes[i][0] = (str[i] == ')') + 1;
  if (rem.upper_bound(i) == rem.end()) nxt[i][0] = i;
  else nxt[i][0] = *rem.upper_bound(i);
  for (int j = 1; j < LOG; ++j) {
    hashes[i][j] = (hashes[i][j - 1] + hashes[nxt[i][j - 1]][j - 1] * p3[1 << (j - 1)] % MOD) % MOD;
    nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
  }
  if (beg[i] < 0) return;
  for (int j = i - 1; j != beg[i]; j = beg[j] - 1) collapse(j);
  int b = beg[i];
  hashes[b][0] = (str[b] == ')') + 1;
  nxt[b][0] = *rem.upper_bound(b);
  for (int j = 1; j < LOG; ++j) {
    hashes[b][j] = (hashes[b][j - 1] + hashes[nxt[b][j - 1]][j - 1] * p3[1 << (j - 1)] % MOD) % MOD;
    nxt[b][j] = nxt[nxt[b][j - 1]][j - 1];
  }
  int a = nxt[i][0];
  for (int j = LOG - 1; j >= 0; --j) {
    if (hashes[a][j] == hashes[b][j]) {
      if (ed[nxt[i][0]] < 0 || nxt[a][j] > ed[nxt[i][0]]) continue;
      if (nxt[b][j] > i) continue;
      a = nxt[a][j], b = nxt[b][j];
    }
  }
  if (str[a] < str[b] || (str[a] == str[b] && b < i)) {
    for (int j = beg[i]; j <= i; ++j) rem.erase(j);
  }
}

int main() {
  p3[0] = 1; for (int i = 1; i < MAX_N; ++i) p3[i] = p3[i - 1] * 3 % MOD;
  cin >> str; str += '(';
  int n = str.size();
  beg.resize(n, -1), ed.resize(n, -1);
  vector<int> last(2 * n + 1, -2);
  int at = n;
  for (int i = 0; i < n; ++i) {
    at += str[i] == '(' ? 1 : -1;
    if (str[i] == ')') beg[i] = last[at] + 1;
    if (str[i] == ')' && last[at] >= -1) ed[last[at] + 1] = i;
    last[at] = i;
  }
  ed[n - 1] = n - 2;
  for (int i = 0; i < n; ++i) rem.insert(i);
  for (int i = n - 1; i >= 0; i = (beg[i] < 0 ? i - 1 : beg[i] - 1)) collapse(i);
  for (int i = 0; i < n - 1; ++i) if (rem.count(i)) cout << str[i];
  cout << '\n';
  return 0;
}
