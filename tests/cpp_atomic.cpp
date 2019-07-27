#include <atomic>

int test()
{
  std::atomic<int> x(3);
  int before = x.fetch_add(2);
  return x.load();
}
