import java.io.*;
import java.util.*;

public class NashMatrix {

  private static final int[] DX = {-1, 1, 0, 0}, DY = {0, 0, -1, 1},
          REMAP = {1, 0, 3, 2};
  private static final char[] MAP = {'U', 'D', 'L', 'R'};

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);
    int n = Integer.parseInt(in.readLine());
    Coordinate[][] board = new Coordinate[n][n];
    String[] line;
    for (int i = 0; i < n; i++) {
      line = in.readLine().split(" ");
      for (int j = 0; j < n; j++)
        board[i][j] = new Coordinate(Integer.parseInt(line[2 * j]) - 1, Integer.parseInt(line[2 * j + 1]) - 1);
    }
    char[][] ans = new char[n][n];
    // Finds the answer for all squares with value (-1, -1):
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (board[i][j].x >= 0) continue;
        for (int k = 0; k < DX.length; k++) {
          int x = i + DX[k], y = j + DY[k];
          if (x < 0 || y < 0 || x >= n || y >= n || board[x][y].x >= 0) continue;
          ans[i][j] = MAP[k];
          break;
        }
        // If the square is not adjacent to any square with value (-1, -1), then a cycle is impossible.
        // Therefore, our answer is "INVALID":
        if (ans[i][j] == '\u0000') {
          out.println("INVALID");
          out.close();
          return;
        }
      }
    }
    // Finds the answer for all squares with value not (-1, -1):
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (ans[i][j] != '\u0000') continue;
        Coordinate cd = board[i][j];
        Coordinate cd2 = board[cd.x][cd.y];
        // Outputs "INVALID" if the value of the square at (cd) is not (cd):
        if (!cd.equals(cd2)) {
          out.println("INVALID");
          out.close();
          return;
        }
        // Floods all squares with value (cd) starting from (cd).
        floodFill(board, ans, cd);
        // Outputs "INVALID" if the flood doesn't reach (i, j):
        if (ans[i][j] == '\u0000') {
          out.println("INVALID");
          out.close();
          return;
        }
      }
    }
    // Output:
    out.println("VALID");
    for (char[] row : ans) {
      for (char ch : row) out.print(ch);
      out.println();
    }
    out.close();
  }

  private static void floodFill(Coordinate[][] board, char[][] ans, Coordinate cur) {
    ans[cur.x][cur.y] = 'X';
    Queue<Coordinate> queue = new LinkedList<>();
    queue.add(cur);
    while (!queue.isEmpty()) {
      cur = queue.poll();
      for (int i = 0; i < DX.length; i++) {
        int x = cur.x + DX[i], y = cur.y + DY[i];
        if (x < 0 || y < 0 || x >= board.length || y >= board[x].length ||
            !board[x][y].equals(board[cur.x][cur.y]) || ans[x][y] != '\u0000') continue;
        ans[x][y] = MAP[REMAP[i]];
        queue.add(new Coordinate(x, y));
      }
    }
  }

  private static class Coordinate {

    private final int x, y;

    private Coordinate(int x, int y) {
      this.x = x;
      this.y = y;
    }

    @Override
    public boolean equals(Object other) {
      if (other == this) return true;
      if (other == null || other.getClass() != Coordinate.class) return false;
      Coordinate cd = (Coordinate) other;
      return cd.x == x && cd.y == y;
    }
  }
}
