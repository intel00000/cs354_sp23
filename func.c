extern int x;
extern int y;
extern int z;
void func() {
  x = x + y;
  y = 4 + z;
  z = x + y;
}