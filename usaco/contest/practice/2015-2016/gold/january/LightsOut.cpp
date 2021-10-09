import java.io.*;
import java.util.*;

public class LightsOut {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new FileReader("lightsout.in"));
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lightsout.out")));
    int n = Integer.parseInt(in.readLine());
    Coor[] v = new Coor[n];
    String[] line;
    for (int i = 0; i < n; ++i) {
      line = in.readLine().split(" ");
      v[i] = new Coor(Integer.parseInt(line[0]), Integer.parseInt(line[1]));
    }
    // Finds the type of corner (convex or concave) at each point:
    for (int i = 0; i < n; ++i) {
      Coor last = v[(i - 1 + n) % n], now = v[i], next = v[(i + 1) % n];
      if (last.x == now.x) {
        if (last.y > now.y) {
          if (now.x < next.x) Path.TYPE.put(now, 1);
          else Path.TYPE.put(now, 0);
        } else {
          if (now.x < next.x) Path.TYPE.put(now, 0);
          else Path.TYPE.put(now, 1);
        }
	  } else {
        if (last.x > now.x) {
          if (now.y < next.y) Path.TYPE.put(now, 0);
          else Path.TYPE.put(now, 1);
        } else {
          if (now.y < next.y) Path.TYPE.put(now, 1);
          else Path.TYPE.put(now, 0);
        }
      }
    }
    // Finds the minimum distance to the exit from each point:
    int d1 = 0, d2 = 0;
    for (int i = 0; i < n; ++i) d1 += v[i].dist(v[(i + 1) % n]);
    int[] md = new int[n];
    for (int i = 0; i < n; ++i) {
      md[i] = Math.min(d1, d2);
      int dist = v[i].dist(v[(i + 1) % n]);
      d1 -= dist; d2 += dist;
    }
    // Finds the number of each path so we know whether a path is unique or not:
    Map<Path, Integer> map = new HashMap<>();
    for (int i = 1; i < n; ++i) {
      List<Coor> p = new ArrayList<>();
      p.add(v[i]);
      for (int j = i + 1; j < n; ++j) {
        p.add(v[j]);
        Path path = new Path(p);
        map.put(path, map.getOrDefault(path, 0) + 1);
      }
    }
    int ans = 0;
    for (int i = 1; i < n; ++i) {
      int reg = md[i], dist = 0;
      List<Coor> p = new ArrayList<>();
      p.add(v[i]);
      boolean done = false;
      for (int j = i + 1; j < n; ++j) {
        p.add(v[j]);
        dist += v[j].dist(v[j - 1]);
        if (map.get(new Path(p)) == 1) {
          dist += md[j];
          done = true;
          break;
        }
      }
      if (!done) dist += v[0].dist(v[n - 1]);
      ans = Math.max(ans, dist - reg);
    }
    // Output:
    out.println(ans);
    out.close();
  }

  private static class Coor {

    private final int x, y;

    private Coor(int x, int y) { this.x = x; this.y = y; }

    private int dist(Coor other) { return Math.abs(x + y - other.x - other.y); }

    @Override
    public int hashCode() {
      return Objects.hash(x, y);
    }

    @Override
    public boolean equals(Object other) {
      Coor c = (Coor) other;
      return c.x == x && c.y == y;
    }
  }
  
  private static class Path {

    private static final Map<Coor, Integer> TYPE = new HashMap<>();

    private final Coor[] path;

    private Path(List<Coor> path) {
      this.path = new Coor[path.size()];
      for (int i = 0; i < this.path.length; ++i) this.path[i] = path.get(i);
    }

    @Override
    public int hashCode() {
      int[] hp = new int[path.length * 2 - 1];
      for (int i = 0; i < path.length; ++i) hp[i] = TYPE.get(path[i]);
      for (int i = 1; i < path.length; ++i) hp[path.length + i - 1] = path[i].dist(path[i - 1]);
      return Arrays.hashCode(hp);
    }

    @Override
    public boolean equals(Object other) {
      Coor[] op = ((Path) other).path;
      if (op.length != path.length) return false;
      for (int i = 0; i < path.length; ++i) {
        if (TYPE.get(op[i]) != TYPE.get(path[i]) ||
          (i > 0 && op[i].dist(op[i - 1]) != path[i].dist(path[i - 1]))) return false;
      }
      return true;
    }
  }
}
