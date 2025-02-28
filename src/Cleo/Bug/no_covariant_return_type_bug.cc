//*
// Martin Lohner, September 1999
// Some of our compilers don't support covariant-return-types for 
// virtual functions yet.

#include "Experiment/Experiment.h"

class BaseReturnType
{
};

class DerivedReturnType : public BaseReturnType
{
};

class Base
{
   public:
      virtual BaseReturnType* virtFunction() { return new BaseReturnType; }
};

class Derived : public Base
{
   public:
#if defined(NO_COVARIANT_RETURN_TYPE_BUG)
      virtual BaseReturnType* virtFunction() { return new DerivedReturnType; }
#else
      virtual DerivedReturnType* virtFunction() { return new DerivedReturnType; }
#endif
};


int main()
{
}
