#include <bits/stdc++.h>
using namespace std;

#define cd complex<double>

const double PI = acos(-1);
const int MAX_X = 1e6 + 1;

void fft(vector<cd>& a, bool inv) {
  int n = a.size();
  if (n == 1) return;
  vector<cd> a0(n >> 1), a1(n >> 1);
  for (int i = 0; 2 * i < n; ++i) a0[i] = a[2 * i], a1[i] = a[2 * i + 1];
  fft(a0, inv), fft(a1, inv);
  double ang = 2 * PI / n * (inv ? -1 : 1);
  cd w(1), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < n; ++i) {
    a[i] = a0[i] + w * a1[i], a[i + (n >> 1)] = a0[i] - w * a1[i];
    if (inv) a[i] /= 2, a[i + (n >> 1)] /= 2;
    w *= wn;
  }
}

vector<int> mult(vector<int>& a, vector<int>& b) {
  vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < a.size() + b.size()) n <<= 1;
  fa.resize(n), fb.resize(n);
  fft(fa, false), fft(fb, false);
  for (int i = 0; i < n; ++i) fa[i] *= fb[i];
  fft(fa, true);
  vector<int> ans(n);
  for (int i = 0; i < n; ++i) ans[i] = round(fa[i].real());
  return ans;
}

int main() {
  int n, x, y; cin >> n >> x >> y; ++n;
  vector<int> arr(x + 1), inv(x + 1);
  for (int i = 0; i < n; ++i) {
    int val; cin >> val;
    arr[val] = 1, inv[x - val] = 1;
  }
  vector<int> pos = mult(arr, inv);
  vector<int> sieve(MAX_X, -1);
  for (int i = 1; i <= x; ++i) if (pos[i + x]) for (int j = i + y; j < MAX_X; j += i + y) sieve[j] = i + y;
  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    int val; cin >> val; val >>= 1;
    if (sieve[val] < 0) cout << -1 << ' ';
    else cout << sieve[val] * 2 << ' ';
  }
  cout << '\n';
  return 0;
}

