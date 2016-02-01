struct A {
  void f() {}
};

struct B : public A {
   virtual void f() {}
};

struct C {
  virtual void f() {}
};

struct D : public C {
  virtual void f() {}
};
