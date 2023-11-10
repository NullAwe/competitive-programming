#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct magic_data {

  vector<int> mapper, endcounts, endcontrib;
  vector<ll> contrib;
  ll answer, enda;
  int len;

  magic_data() : mapper(6), contrib(6), endcontrib(6), endcounts(6), answer(0), len(1), enda(0) {
    endcounts[0] = 1;
    for (int i = 0; i < 6; ++i) mapper[i] = i;
  }

  void change(char ch) {
    for (int i = 0; i < 6; ++i) mapper[i] = contrib[i] = endcounts[i] = endcontrib[i] = 0;
    answer = 0, len = 1, enda = 0;
    endcounts[0] = 1;
    for (int i = 0; i < 6; ++i) mapper[i] = i;
    switch (ch) {
      case 'b':
        mapper[0] = 1, endcounts[0] = 0, endcounts[1] = 1;
        break;
      case 'e':
        mapper[1] = 2, mapper[5] = 0, contrib[5] = endcontrib[5] = 1;
        break;
      case 's':
        mapper[2] = 3, mapper[3] = 4;
        break;
      case 'i':
        mapper[4] = 5;
        break;
    }
  }

  void change(magic_data* x, magic_data* y) {
    for (int i = 0; i < 6; ++i) mapper[i] = contrib[i] = endcounts[i] = endcontrib[i] = 0;
    answer = 0, enda = 0;
    for (int i = 0; i < 6; ++i) mapper[i] = y->mapper[x->mapper[i]];
    endcounts = y->endcounts;
    for (int i = 0; i < 6; ++i) endcounts[y->mapper[i]] += x->endcounts[i];
    for (int i = 0; i < 6; ++i) {
      contrib[i] = x->contrib[i] + x->endcontrib[i] * y->len + y->contrib[x->mapper[i]];
      endcontrib[i] = x->endcontrib[i] + y->endcontrib[x->mapper[i]];
    }
    answer = x->answer + x->enda * y->len + y->answer;
    enda = x->enda + y->enda;
    for (int i = 0; i < 6; ++i) {
      answer += y->contrib[i] * x->endcounts[i];
      enda += y->endcontrib[i] * x->endcounts[i];
    }
    len = x->len + y->len;
  }

  ll do_magic() {
    return answer;
  }
};

struct magic {

  int n;
  vector<magic_data> t;

  magic() {}

  magic(int n) : n(n), t(4 * n) {
    for (int i = 0; i < 4 * n; ++i) {
      magic_data tmp;
      t[i] = tmp;
    }
  }

  void upd_int(int v, int tl, int tr, int x, int ch) {
    if (tl == tr) {
      t[v].change(ch);
    } else {
      int m = (tl + tr) / 2;
      if (x <= m) upd_int(2 * v, tl, m, x, ch);
      else upd_int(2 * v + 1, m + 1, tr, x, ch);
      t[v].change(&t[2 * v], &t[2 * v + 1]);
    }
  }

  void upd(int x, char ch) {
    upd_int(1, 0, n - 1, x, ch);
  }

  ll qry() {
    return t[1].answer;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;
  int n = s.size(), q; cin >> q;
  magic mg(n);
  for (int i = 0; i < n; ++i) mg.upd(i, s[i]);
  cout << mg.qry() << '\n';
  for (int i = 0; i < q; ++i) {
    int x;
    char ch;
    cin >> x >> ch; --x;
    mg.upd(x, ch);
    cout << mg.qry() << '\n';
  }
  return 0;
}