int global_data = 200;

void test ()
{
  int add_res;
  int b = 200, c = 300;
  __asm__ __volatile__("add %0,%1,%2"
                       :"=r"(add_res)
                       :"r"(b), "r"(c)
                       );
  int lw_res;
  int *lw_p = (int *)&global_data;
  __asm__ __volatile__("lw %0, %1"
                       :"=r"(lw_res)
                       :"m"(lw_p)
                       );

  const int imm = 100;
  int addi_res;
  __asm__ __volatile__("addi %0,%1,%2"
                       :"=r"(addi_res) // e=4
                       :"r"(lw_res),"i"(imm)
                       );

}
