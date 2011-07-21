#include<cstdio>

class A
{
  int i;
  public:
    A() { i = 0; }
    void fun() { i++; printf("Hello %d\n", i); }
};

//Or, better use typedefs
typedef void (A::*fptr)();
//fptr p = &A::fun;
//static const fptr q =&A::fun;

int main()
{
  A a;
  A b;
  void (A::* p)() = &A::fun;
  printf("%p\n", (void*)p);
  (a.*p)();
  (a.*p)();
  (b.*p)();
}

