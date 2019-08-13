#include <stdint.h>

int64_t func(int64_t a0, int64_t a1)
{
  return a0 - a1;
}


int main() {
  volatile uint64_t result;
  result = func(10, 20);
}
