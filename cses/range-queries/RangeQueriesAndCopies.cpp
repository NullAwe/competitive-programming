#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Node {

  Node *l, *r;
  ll val;

  Node(ll val) : l(nullptr), r(nullptr), val(val) {}
  Node(Node *l, Node *r) : l(l), r(r), val(0) {
    if (l) val += l->val;
    if (r) val += r->val;
  }
};

Node* build(int tl, int tr) {
  if (tl == tr) return new Node(0);
  int m = (tl + tr) / 2;
  return new Node(build(tl, m), build(m + 1, tr));
}

Node* update(Node *v, int tl, int tr, int p, ll val) {
  if (tl == tr) return new Node(val);
  int m = (tl + tr) / 2;
  if (p <= m) return new Node(update(v->l, tl, m, p, val), v->r);
  return new Node(v->l, update(v->r, m + 1, tr, p, val));
}

ll query(Node *v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (tl == l && tr == r) return v->val;
  int m = (tl + tr) / 2;
  return query(v->l, tl, m, l, min(m, r)) + query(v->r, m + 1, tr, max(m + 1, l), r);
}

int main() {
  int n, q; cin >> n >> q;
  vector<Node*> trees;
  trees.push_back(build(0, n - 1));
  for (int i = 0; i < n; ++i) { int x; cin >> x; trees[0] = update(trees[0], 0, n - 1, i, x); }
  for (int i = 0; i < q; ++i) {
    int t, k; cin >> t >> k; --k;
    if (t == 1) { int p, v; cin >> p >> v; trees[k] = update(trees[k], 0, n - 1, p - 1, v); }
    else if (t == 2) { int a, b; cin >> a >> b; cout << query(trees[k], 0, n - 1, a - 1, b - 1) << '\n'; }
    else trees.push_back(trees[k]);
  }
  return 0;
}
