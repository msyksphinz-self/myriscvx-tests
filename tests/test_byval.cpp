void func (int &a)
{
  a += 3;
}


void call_func () {
  int b = 10;
  func (b);
}
