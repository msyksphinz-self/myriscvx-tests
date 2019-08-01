#include <stdint.h>

int64_t display_frameaddress() {
  return (int64_t)__builtin_frame_address(0);
}

extern int fn();

int display_returnaddress() {
  int64_t a = (int64_t)__builtin_return_address(0);
  fn();
  return a;
}
