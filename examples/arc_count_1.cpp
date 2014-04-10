#include <cassert>
#include <iostream>
#include <typeinfo>

class RCBase
{
  mutable int mRefCount;
public:
  RCBase():mRefCount(0){}
  virtual ~RCBase(){}

  void grab() const {++mRefCount; std::cout << this << " has ref ocunt " << mRefCount << std::endl;}
  void release()
  {
    assert(mRefCount > 0);
    --mRefCount;
    if (mRefCount == 0) { delete this;}
  }
};


class MyClass: public RCBase
{
public:
  ~MyClass(){std::cout << this << " No longer needed" << std::endl;}
  void print(){std::cout << "Hello" << std::endl;}
};


int main()
{
  auto const a = new MyClass();
  a-> grab();

  auto ptr = a;
  ptr-> grab();

  a-> release();
  a= nullptr;  // a points to nothing;
  std::cout << typeid(a).name() << std::endl;

  ptr-> release();
  ptr = nullptr;

  return 0;
}
