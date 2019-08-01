void assembly_code_test ()
{
  asm("sub   x3, x2, x3");
  asm("mul   x2, x1, x3");

  asm("lw    x2, 8(x2)");
  asm("sw    zero, 4(x2)");
  asm("addi  x3, zero, 500");

  // asm("add   a0, a1, a2");

  asm("srai  x2, x2, 2");
  asm("slli  x2, x2, 2");
  asm("srli  x2, x3, 5");

  asm("jr    x6");

  asm("li    x3, 0x00700000");
  asm("la    x3, 0x00900000");
  //  asm("test_label: la    x3, test_label");
}
