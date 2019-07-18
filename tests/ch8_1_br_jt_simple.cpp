int test_br_jt_simple ()
{
  int buff = 0x30;
  int Result = 0;

  switch (buff) {
    case 0x30: Result = 1; break;
    case 0x31: Result = 2; break;
    case 0x32: Result = 3; break;
    case 0x33: Result = 4; break;
  }

  return Result;
}
