int test_slt()
{
  int a = 5;
  int b = 3;
  int c, d, e, f, g, h;

  c = (a == b); // seq, c = 0
  d = (a != b); // sne, d = 1
  e = (a < b);  // slt, e = 0
  f = (a <= b); // sle, f = 0
  g = (a > b);  // sgt, g = 1
  h = (a >= b); // sge, g = 1

  return 0;
}
