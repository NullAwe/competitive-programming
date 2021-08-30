import java.io.*;
import java.util.*;

public class TwoTypesOfSpells {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter out = new PrintWriter(System.out);
    int n = Integer.parseInt(in.readLine()), available = 0;
    // Keeps track of sums to avoid O(n) time to sum:
    long sum = 0, goodSum = 0;
    // Keeps track of moves that we don't double:
    TreeSet<Integer> f = new TreeSet<>(), l = new TreeSet<>();
    // Stores the moves that we double:
    TreeSet<Move> d = new TreeSet<>();
    for (int i = 0; i < n; ++i) {
      String[] line = in.readLine().split(" ");
      int type = Integer.parseInt(line[0]), power = Integer.parseInt(line[1]);
      // Takes care of operations where we add a new move:
      if (power > 0) {
        sum += power;
        if (type == 0) {
          // Takes care of the situation where we can double it:
          if (available > 0) {
            d.add(new Move(power, type));
            goodSum += power;
            --available;
          } else if (d.isEmpty()) f.add(power); // We can't double it.
          else if (power > d.first().power) { // We can double it, but we take out another move.
            // Replaces a move with less power in the double TreeSet with this one:
            Move move = d.pollFirst();
            d.add(new Move(power, type));
            if (move.type == 0) f.add(move.power);
            else l.add(move.power);
            goodSum += power - move.power;
          } else f.add(power); // We can't double it.
        } else {
          // Adds the move to the non-double TreeSet, then finds the best move to add to the doubled TreeSet:
          l.add(power);
          if (!f.isEmpty() && (f.last() >= l.last() || l.size() == 1)) {
            // Adds a fire spell to the doubled TreeSet:
            d.add(new Move(f.last(), 0));
            goodSum += f.pollLast();
          } else if (l.size() > 1) {
            // Adds a lightning spell to the doubled TreeSet:
            d.add(new Move(l.last(), 1));
            goodSum += l.pollLast();
          } else {
            // Signifies that we cannot add right now, but we can add the next move that comes in:
            ++available;
          }
        }
      } else {
        // Takes care of the operation where we remove a move:
        power = -power;
        sum -= power;
        if (type == 0) {
          if (f.contains(power)) f.remove(power); // We don't have to change anything else.
          else {
            // Removes move from the doubled TreeSet: and adds the next best move to the TreeSet:
            d.remove(new Move(power, type));
            goodSum -= power;
            if (!f.isEmpty() && (f.last() >= l.last() || l.size() == 1)) {
              // Adds a fire spell to the doubled TreeSet:
              d.add(new Move(f.last(), 0));
              goodSum += f.pollLast();
            } else if (l.size() > 1) {
              // Adds a lightning spell to the doubled TreeSet:
              d.add(new Move(l.last(), 1));
              goodSum += l.pollLast();
            } else {
              // Signifies that we cannot add right now, but we can add the next move that comes in:
              ++available;
            }
          }
        } else {
          if (l.contains(power)) {
            // Removes move from the non-doubled TreeSet, and takes away worst move from the doubled TreeSet:
            l.remove(power);
            if (l.isEmpty() && !d.isEmpty()) {
              Move move = d.pollFirst();
              if (move.type == 0) { // We don't take fire spell right now.
                // Takes care of the case where we have no choice but to remove the fire spell:
                if (d.isEmpty()) {
                  f.add(move.power);
                  goodSum -= move.power;
                } else {
                  // Removes the worst lightning spell and adds the fire spell back:
                  Move second = d.pollFirst();
                  l.add(second.power);
                  d.add(move);
                  goodSum -= second.power;
                }
              } else {
                // Removes the worst lightnign spell:
                l.add(move.power);
                goodSum -= move.power;
              }
            } else if (l.isEmpty() && d.isEmpty()) {
              // Signifies that we can no longer add the next move that comes in:
              --available;
            } else {
              // Removes the worst move and puts it in the correct TreeSet:
              Move move = d.pollFirst();
              if (move.type == 0) f.add(move.power);
              else l.add(move.power);
              goodSum -= move.power;
            }
          } else {
            // Removes the move from the doubled TreeSet:
            goodSum -= power;
            d.remove(new Move(power, type));
          }
        }
      }
      // Output:
      out.println(sum + goodSum);
    }
    out.close();
  }

  // Used to store information about move type in the doubled TreeSet:
  private static class Move implements Comparable<Move> {

    private final int power, type;

    private Move(int p, int t) {
      power = p;
      type = t;
    }

    public int compareTo(Move other) {
      if (power != other.power) return power - other.power;
      return other.type - type;
    }
  }
}
