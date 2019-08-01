#include <stdint.h>

bool exceptionOccur = false;
void* returnAddr;

// Even though __builtin_frame_address is useless in this example, I believe
// it will be used in real exception handler implementation. Because in real
// implementation, the exception handler keeps a table and decide which function
// should be triggered for a specific exception and hand over to it.
// The hand over process needs unwinding the stack frame. The stack frame address
// can be gotten by calling __builtin_frame_address in the charged function.
void exception_handler() {
  exceptionOccur = true;
  int64_t frameaddr = (int64_t)__builtin_frame_address(0);
  __builtin_eh_return(0, returnAddr); // no warning, eh_return never returns.
}

__attribute__ ((weak))
int test_detect_exception(bool exception) {
  exceptionOccur = false;
  void* handler = (void*)(&exception_handler);
  if (exception) {
    returnAddr = __builtin_return_address(0);
    __builtin_eh_return(0, handler); // no warning, eh_return never returns.
  }
  else {
    return 0;
  }
}
