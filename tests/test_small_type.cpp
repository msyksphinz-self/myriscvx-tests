#include <stdint.h>

int8_t test_int8_type ()
{
  volatile int8_t i8  = 0xab;
  int8_t i8_2 = i8 + 4;
  return i8_2;
}


uint8_t test_uint8_type ()
{
  volatile uint8_t  u8  = 0xab;
  uint8_t u8_2 = u8 + 4U;
  return u8_2;
}
