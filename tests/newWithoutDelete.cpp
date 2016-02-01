#include <stddef.h>

class A {
public:
  void *operator new(size_t size) throw() {
    return NULL;
  };
};

class B {
public:
  void *operator new(size_t size) throw() {
    return NULL;
  };

  void operator delete(void *ptr) throw() {};
};
