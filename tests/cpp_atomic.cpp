#include <atomic>

int test()
{
  std::atomic<int> x(3);
  int before_add = x.fetch_add(2);
  int before_sub = x.fetch_sub(3);
  return x.load();
}
