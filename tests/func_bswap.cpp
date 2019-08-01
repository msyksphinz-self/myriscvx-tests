int test_bswap16() {
  volatile int a = 0x1234;
  int result = (__builtin_bswap16(a) ^ 0x3412);

  return result;
}

int test_bswap32() {
  volatile int a = 0x1234;
  int result = (__builtin_bswap32(a) ^ 0x34120000);

  return result;
}

int test_bswap64() {
  volatile int a = 0x1234;
  int result = (__builtin_bswap64(a) ^ 0x3412000000000000);

  return result;
}

int test_bswap() {
  int result = test_bswap16() + test_bswap32() + test_bswap64();

  return result;
}
