// clang -target mips-unknown-linux-gnu -c ch7_1_localpointer.cpp -emit-llvm -o ch7_1_localpointer.bc
// ~/llvm/test/cmake_debug_build/Debug/bin/llc -march=cpu0 -relocation-model=pic -filetype=asm ch7_1_localpointer.bc -o -

/// start
int test_local_pointer()
{
  int b = 3;
  int* p = &b;

  return 0;
}
