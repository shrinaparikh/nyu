
// This code, when compiled to assembly, shows how some of the parameters
// are passed in registers and some are pushed onto the stack. See
// the version of args.s for your OS (Unix or Windows).

int foo(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

void g()
{
  foo(1,2,3,4,5,6,7,8,9,10);
}
