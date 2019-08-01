#include <stdint.h>
#include <atomic>

std::atomic<int32_t> x32;
std::atomic<int16_t> x16;
std::atomic<int8_t > x8;

int32_t test_32()
{
  x32.fetch_add(2);
  return x32.load();
}

int16_t test_16()
{
  x16.fetch_add(2);
  return x16.load();
}

int8_t test_8()
{
  x8.fetch_add(2);
  return x8.load();
}


int main ()
{
}
