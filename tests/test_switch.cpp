int test_value = 0x30;  // 0x30, 0x31, ... ,0x35
int a_val = 0;
int b_val = 0;

void test_switch ()
{
  int result = 0;

  switch (test_value)
  {
    case 0x30:
      if (a_val == b_val)
        result = 1;
      break;
    case 0x31:
      if (a_val != b_val)
        result = 1;
      break;
    case 0x32:
      if (a_val > b_val)
        result = 1;
      break;
    case 0x33:
      if (a_val < b_val)
        result = 1;
      break;
    case 0x34:
      if (a_val >= b_val)
        result = 1;
      break;
    case 0x35:
      if (a_val <= b_val)
        result = 1;
      break;
  }
  return;
}
