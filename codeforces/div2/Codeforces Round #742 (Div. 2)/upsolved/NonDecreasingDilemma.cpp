#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Used for storing information in the segment tree:
struct Info {
  ll l, r, pref, post, value;
};

void build(vector<Info*>& t, vector<int>& arr) {
  for (int i = arr.size() - 1; i > 0; --i) {
    t[i]->value = t[i << 1]->value + t[i << 1 | 1]->value;
    t[i]->pref = t[i << 1]->pref;
    t[i]->post = t[i << 1 | 1]->post;
    t[i]->l = t[i << 1]->l;
    t[i]->r = t[i << 1 | 1]->r;
    if (arr[t[i << 1]->r] <= arr[t[i << 1 | 1]->l]) {
      ll a = t[i << 1]->post, b = t[i << 1 | 1]->pref;
      t[i]->value += (a + b) * (a + b + 1) / 2 - a * (a + 1) / 2 - b * (b + 1) / 2;
      if (a * (a + 1) / 2 == t[i << 1]->value) t[i]->pref = a + b;
      if (b * (b + 1) / 2 == t[i << 1 | 1]->value) t[i]->post = a + b;
    }
  }
}

void modify(vector<Info*>& t, int p, ll value, vector<int>& arr) {
  for (t[p += arr.size()]->value = 1; p > 1; p >>= 1) {
    int i = p >> 1;
    t[i]->value = t[i << 1]->value + t[i << 1 | 1]->value;
    t[i]->pref = t[i << 1]->pref;
    t[i]->post = t[i << 1 | 1]->post;
    if (arr[t[i << 1]->r] <= arr[t[i << 1 | 1]->l]) {
      ll a = t[i << 1]->post, b = t[i << 1 | 1]->pref;
      t[i]->value += (a + b) * (a + b + 1) / 2 - a * (a + 1) / 2 - b * (b + 1) / 2;
      if (a * (a + 1) / 2 == t[i << 1]->value) t[i]->pref = a + b;
      if (b * (b + 1) / 2 == t[i << 1 | 1]->value) t[i]->post = a + b;
    }
  }
}

ll query(vector<Info*>& t, int l, int r, vector<int>& arr) {
  vector<Info*> left, right;
  for (l += arr.size(), r += arr.size(); l < r; l >>= 1, r >>= 1) {
    if (l & 1) left.push_back(t[l++]);
    if (r & 1) right.push_back(t[--r]);
  }
  for (int i = right.size() - 1; i >= 0; --i) left.push_back(right[i]);
  ll res = 0, last = INT_MAX, lastLen = INT_MAX;
  for (Info* info : left) {
    res += info->value;
    if (last <= arr[info->l]) {
      ll a = info->pref, b = lastLen;
      res += (a + b) * (a + b + 1) / 2 - a * (a + 1) / 2 - b * (b + 1) / 2;
    }
    if (last <= arr[info->l] && (info->pref == info->r - info->l + 1)) lastLen += info->pref;
    else lastLen = info->post;
    last = arr[info->r];
  }
  return res;
}

int main() {
  int n, q; cin >> n >> q;
  ll size = 1;
  while (2 * n > size) size *= 2;
  int nn = (int) (size / 2);
  vector<int> arr(nn);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  // Creates the segment tree:
  vector<Info*> t(size);
  for (int i = 0; i < size; ++i) {
    t[i] = new Info;
    t[i]->value = t[i]->pref = t[i]->post = t[i]->l = t[i]->r = 0;
  }
  for (int i = 0; i < nn; ++i) {
    t[nn + i]->value = t[nn + i]->pref = t[nn + i]->post = 1;
    t[nn + i]->l = t[nn + i]->r = i;
    if (i >= n) t[nn + i]->value = t[nn + i]->pref = t[nn + i]->post = 0;
  }
  build(t, arr);
  for (int i =0 ; i < q; ++i) {
    ll type; cin >> type;
    ll a, b; cin >> a >> b;
    if (type == 1) {
      // Modifies an element using the segment tree:
      arr[a - 1] = b;
      modify(t, a - 1, b, arr);
    } else {
      // Output:
      cout << query(t, a - 1, b, arr) << '\n';
    }
  }
  return 0;
}
