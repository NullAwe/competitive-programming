#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

void solve() {
  int n, mx = 0, incyc; cin >> n; incyc = n;
  vector<int> arr(n), counts(n + 1);
  ll sum = 0;
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
    ++counts[arr[i]], mx = max(mx, arr[i]), sum += arr[i];
    if (arr[i] == 1) --incyc;
  }
  if (sum != 2 * n) {
    cout << "No\n";
    return;
  }
  if (incyc == n) {
    cout << "Yes\n";
    for (int i = 0; i < n; ++i) cout << i + 1 << ' ' << (i + 1) % n + 1 << '\n';
    return;
  }
  if (!counts[2]) {
    cout << "Yes\n";
    vector<int> gr(n - counts[1]), os(counts[1]);
    int ai = 0, bi = 0;
    for (int i = 0; i < n; ++i) {
      if (arr[i] == 1) os[bi++] = i;
      else gr[ai++] = i;
    }
    bi = 0;
    for (int i = 0; i < n - counts[1]; ++i) {
      cout << gr[i] + 1 << ' ' << gr[(i + 1) % (n - counts[1])] + 1 << '\n';
      for (int j = 2; j < arr[gr[i]]; ++j) cout << gr[i] + 1 << ' ' << os[bi++] + 1 << '\n';
    }
    return;
  }
  if (incyc == 3 || counts[2] == incyc - 1 || (mx == 3 && incyc % 2 == 1 && (counts[3] == 2 || incyc == 5))) {
    cout << "No\n";
    return;
  }
  cout << "Yes\n";
  vector<pii> na(n); for (int i = 0; i < n; ++i) na[i] = {arr[i], i};
  sort(na.begin(), na.end());
  bool odd = incyc & 1; incyc = 2;
  vector<int> cyc(2);
  for (int i = 0; i < 2; ++i) {
    cyc[i] = na.back().second;
    na.resize((int) na.size() - 1);
  }
  for (int i = 0; i < 2; ++i) {
    cout << cyc[i] + 1 << ' ' << cyc[(i + 1) & 1] + 1 << '\n';
    arr[cyc[i]] -= 2;
  }
  int idx = 1, cnt = 0, ai = 0;
  vector<int> ones(counts[1]), latest(2);
  reverse(na.begin(), na.end());
  for (pii pp : na) {
    if (pp.first > 1) {
      if (cnt < 2) {
        cout << pp.second + 1 << ' ' << cyc[cnt] + 1 << '\n';
        --arr[cyc[cnt]], --arr[pp.second];
        latest[cnt] = pp.second;
      } else if (cnt == 2 && odd) {
        int idx = arr[cyc[0]] == 0;
        if (arr[cyc[idx]] == 0) {
          cout << pp.second + 1 << ' ' << latest[0] + 1 << '\n';
          --arr[latest[0]], --arr[pp.second];
        } else {
          cout << pp.second + 1 << ' ' << cyc[idx] + 1 << '\n';
          --arr[cyc[idx]], --arr[pp.second];
          latest[idx] = pp.second;
        }
      } else {
        cout << pp.second + 1 << ' ' << latest[cnt & 1] + 1 << '\n';
        --arr[pp.second], --arr[latest[cnt & 1]];
        latest[cnt & 1] = pp.second;
      }
      ++cnt;
    } else ones[ai++] = pp.second;
  }
  ai = 0;
  for (pii pp : na)
    if (pp.first > 1)
      for (int i = 0; i < arr[pp.second]; ++i)
        cout << pp.second + 1 << ' ' << ones[ai++] + 1 << '\n';
  for (int num : cyc)
    for (int i = 0; i < arr[num]; ++i)
      cout << num + 1 << ' ' << ones[ai++] + 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
