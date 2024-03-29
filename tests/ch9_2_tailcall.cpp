// clang -O1 -target mips-unknown-linux-gnu -c ch9_2_tailcall.cpp -emit-llvm -o ch9_2_tailcall.bc
// ~llvm/test/cmake_debug_build/bin/llc -march=cpu0 -mcpu=cpu032II -relocation-model=static -filetype=asm -enable-cpu0-tail-calls -view-isel-dags ch9_2_tailcall.bc -stats -o -
// ~/llvm/test/cmake_debug_build/bin/llc -march=cpu0 -mcpu=cpu032II -relocation-model=static -filetype=asm -enable-cpu0-tail-calls -view-sched-dags ch9_2_tailcall.bc -stats -o -

// ~/llvm/test/cmake_debug_build/debug/bin/llc -march=cpu0 -mcpu=cpu032II -relocation-model=static -filetype=asm -enable-cpu0-tail-calls ch9_2_tailcall.bc -stats -o -
/// start

int tailcall (int a, int b)
{
  return a + b;
}

int test_tailcall(int a, int b)
{
  return tailcall(b, a);
}
