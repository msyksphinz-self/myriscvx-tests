int sum(int a, int b)
{
  return a - b;
  // if (a > 0)
  //   return sum(a - 1, b * 2);
  // else
  //   return b;
}

int test_tailcall(int a, int b)
{
  return sum(a, b);
}
