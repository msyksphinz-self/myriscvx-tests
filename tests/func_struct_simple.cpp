#include <stdio.h>

struct S
{
  int x[17];
};

void func (struct S elem) {
  for(int i = 0; i < 17; i++) {
    elem.x[i] ++;
  }
}

void call_func () {
  struct S elem;
  for (int i = 0; i < 17; i++) {
    elem.x[i] = i;
  }
  func (elem);
}
