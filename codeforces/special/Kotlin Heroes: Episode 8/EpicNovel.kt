fun main() {
  val t = readLine()?.toIntOrNull() ?: 0
  for (i in 1..t) solve()
}

fun solve() {
  val n = readLine()?.toIntOrNull() ?: 0
  var line = readLine()
  if (line == null) line = ""
  var split = line.split(" ").toTypedArray()
  val a = split.elementAt(0).toInt()
  val va = split.elementAt(1).toInt()
  line = readLine()
  if (line == null) line = ""
  split = line.split(" ").toTypedArray()
  val c = split.elementAt(0).toInt()
  val vc = split.elementAt(1).toInt()
  val b = readLine()?.toIntOrNull() ?: 0
  // Output:
  if (vc - c + b < va) println(va)
  else println(vc - c + b)
}
