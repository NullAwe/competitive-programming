#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m; cin >> n >> m;
  vector<vector<int>> arr(n, vector<int>(m));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> arr[i][j];
  vector<int> consider;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (arr[j][i] != arr[0][i]) {
        consider.push_back(i);
        break;
      }
    }
  }
  if (consider.size() > 2 * n) {
    cout << "No\n";
    return 0;
  }
  vector<int> diff(n);
  for (int i = 1; i < n; ++i) for (int j = 0; j < m; ++j) diff[i] += (arr[0][j] != arr[i][j]);
  for (int i = 1; i < n; ++i) {
    if (diff[i] > 2) break;
    if (i == n - 1) {
      cout << "Yes\n";
      for (int num : arr[0]) cout << num << ' ';
      cout << '\n';
      return 0;
    }
  }
  for (int i = 0; i < consider.size(); ++i) {
    int a = consider[i];
    vector<int> copy = diff;
    for (int j = 1; j < n; ++j) copy[j] -= (arr[0][a] != arr[j][a]);
    for (int j = 1; j < n; ++j) {
      if (copy[j] > 2) break;
      if (copy[j] == 2) {
        for (int k = 1; k < n; ++k) {
          if (j == k) continue;
          copy[k] += (arr[j][a] != arr[k][a]);
        }
        for (int k = 1; k < n; ++k) {
          if (copy[k] > 2) break;
          if (k == n - 1) {
            cout << "Yes\n";
            for (int l = 0; l < m; ++l) {
              if (l == a) cout << arr[j][l] << ' ';
              else cout << arr[0][l] << ' ';
            }
            cout << '\n';
            return 0;
          }
        }
        break;
      }
    }
  }
  for (int i = 0; i < consider.size(); ++i) {
    for (int j = i + 1; j < consider.size(); ++j) {
      int a = consider[i], b = consider[j];
      vector<int> copy = diff;
      for (int k = 1; k < n; ++k) copy[k] -= (arr[0][a] != arr[k][a]) + (arr[0][b] != arr[k][b]);
      bool works = true;
      for (int k = 1; k < n; ++k) {
        if (!copy[k]) continue;
        if (copy[k] > 2) {
          works = false;
          break;
        }
        if (copy[k] == 2) {
          for (int l = 1; l < n; ++l) {
            if (k == l) continue;
            copy[l] += (arr[k][a] != arr[l][a]) + (arr[k][b] != arr[l][b]);
          }
          for (int l = 1; l < n; ++l) {
            if (copy[l] > 2) {
              works = false;
              break;
            }
          }
          if (!works) break;
          cout << "Yes\n";
          for (int l = 0; l < m; ++l) {
            if (l == a || l == b) cout << arr[k][l] << ' ';
            else cout << arr[0][l] << ' ';
          }
          cout << '\n';
          return 0;
        }
        if (!works) break;
      }
      if (!works) continue;
      for (int k = 1; k < n; ++k) {
        if (copy[k] != 1) continue;
        vector<int> tries = {a, b};
        vector<int> other = {b, a};
        for (int num = 0; num < 2; ++num) {
          int _try = tries[num], _oth = other[num];
          vector<int> sc = copy;
          for (int l = 1; l < n; ++l) {
            if (l == k || sc[l] != 1) continue;
            sc[l] += (arr[k][_try] != arr[l][_try]);
          }
          bool works2 = true;
          for (int l = 1; l < n; ++l) {
            if (sc[l] == 2) {
              for (int ii = 1; ii < n; ++ii) {
                if (l == ii) continue;
                sc[ii] += (arr[l][_oth] != arr[ii][_oth]);
              }
              for (int ii = 1; ii < n; ++ii) {
                if (sc[ii] > 2) {
                  works2 = false;
                  break;
                }
              }
              if (works2) {
                cout << "Yes\n";
                for (int ii = 0; ii < m; ++ii) {
                  if (ii == _try) cout << arr[k][ii] << ' ';
                  else if (ii == _oth) cout << arr[l][ii] << ' ';
                  else cout << arr[0][ii] << ' ';
                }
                cout << '\n';
                return 0;
              }
              break;
            }
          }
          if (works2) {
            cout << "Yes\n";
            for (int l = 0; l < m; ++l) {
              if (l == _try || l == _oth) cout << arr[k][l] << ' ';
              else cout << arr[0][l] << ' ';
            }
            cout << '\n';
            return 0;
          }
        }
        break;
      }
    }
  }
  cout << "No\n";
  return 0;
}
