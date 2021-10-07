fun main() {
  val t = readLine()?.toIntOrNull() ?: 0
  for (i in 1..t) solve()
}

fun solve() {
  var seq = readLine()
  if (seq == null) seq = ""
  // Output:
  if (seq.contains("<") && seq.contains(">")) println("?")
  else if (seq.contains("<")) println("<")
  else if (seq.contains(">")) println(">")
  else println("=")
}
