#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int BUFFER_SIZE = 1 << 16;

char input_buffer[BUFFER_SIZE];
size_t input_pos = 0, input_len = 0;

char output_buffer[BUFFER_SIZE];
int output_pos = 0;

char number_buffer[100];
uint8_t lookup[100];

void _update_input_buffer() {
    input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
    input_pos = 0;

    if (input_len == 0)
        input_buffer[0] = EOF;
}

inline char next_char(bool advance = true) {
    if (input_pos >= input_len)
        _update_input_buffer();

    return input_buffer[advance ? input_pos++ : input_pos];
}

template <typename T>
inline void read_int(T& number) {
    bool negative = false;
    number = 0;

    while (!isdigit(next_char(false)))
        if (next_char() == '-')
            negative = true;

    do {
        number = 10 * number + (next_char() - '0');
    } while (isdigit(next_char(false)));

    if (negative)
        number = -number;
}

template <typename T, typename... Args>
inline void read_int(T& number, Args&... args) {
    read_int(number);
    read_int(args...);
}

void _flush_output() {
    fwrite(output_buffer, sizeof(char), output_pos, stdout);
    output_pos = 0;
}

inline void write_char(char c) {
    if (output_pos == BUFFER_SIZE)
        _flush_output();

    output_buffer[output_pos++] = c;
}

template <typename T>
inline void write_int(T number, char after = '\0') {
    if (number < 0) {
        write_char('-');
        number = -number;
    }

    int length = 0;

    while (number >= 10) {
        uint8_t lookup_value = lookup[number % 100];
        number /= 100;
        number_buffer[length++] = char((lookup_value & 15) + '0');
        number_buffer[length++] = char((lookup_value >> 4) + '0');
    }

    if (number != 0 || length == 0)
        write_char(char(number + '0'));

    for (int i = length - 1; i >= 0; i--)
        write_char(number_buffer[i]);

    if (after)
        write_char(after);
}

void init() {
    // Make sure _flush_output() is called at the end of the program.
    bool exit_success = atexit(_flush_output) == 0;
    assert(exit_success);

    for (int i = 0; i < 100; i++)
        lookup[i] = uint8_t((i / 10 << 4) + i % 10);
}
}  // namespace IO

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  IO::init();
  int n, q; IO::read_int(n, q);
  vector<deque<int>> seqs(n + q);
  vector<unordered_map<int, int, custom_hash>> ms(n + q);
  for (int i = 0; i < n; ++i) {
    int m; IO::read_int(m);
    for (int j = 0; j < m; ++j) {
      int x; IO::read_int(x);
      seqs[i].push_back(x);
      ++ms[i][x];
    }
  }
  for (int i = 0; i < q; ++i) {
    int t; IO::read_int(t);
    if (t == 1) {
      int x, y; IO::read_int(x, y);
      seqs[x - 1].push_back(y), ++ms[x - 1][y];
    } else if (t == 2) {
      int x; IO::read_int(x);
      --ms[x - 1][seqs[x - 1].back()];
      seqs[x - 1].pop_back();
    } else if (t == 3) {
      int m; IO::read_int(m);
      vector<int> idx(m); for (int j = 0; j < m; ++j) IO::read_int(idx[j]);
      for (int j = 0; j < m; ++j) --idx[j];
      vector<int> szs(m + 1);
      for (int i = 0; i < m; ++i) szs[i + 1] = szs[i] + seqs[idx[i]].size();
      int len = szs.back(), mode = -1;
      for (int it = 0; it < 18; ++it) {
        int rd = rng() % len, has = 0;
        int id = upper_bound(szs.begin(), szs.end(), rd) - szs.begin();
        int x = seqs[idx[id - 1]][rd - szs[id - 1]];
        for (int num : idx) has += ms[num][x];
        if (has > len / 2) {
          mode = x;
          break;
        }
      }
      IO::write_int(mode, '\n');
    } else {
      int x1, x2, x3; IO::read_int(x1, x2, x3); --x1, --x2, --x3;
      swap(seqs[x1], seqs[x3]), swap(ms[x1], ms[x3]);
      bool flip = false;
      if (seqs[x2].size() > seqs[x3].size()) {
        swap(seqs[x2], seqs[x3]), swap(ms[x2], ms[x3]);
        reverse(seqs[x2].begin(), seqs[x2].end());
        flip = true;
      }
      for (int num : seqs[x2]) {
        if (flip) seqs[x3].push_front(num);
        else seqs[x3].push_back(num);
        ++ms[x3][num];
      }
    }
  }
  return 0;
}