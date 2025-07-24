//*
// Martin Lohner, July 17, 1998
// The solaris compiler (CC 4.2) gives a warning when virtual base functions
// are overloaded, and one is overriden in derived class.
// It works ok though!
#include "Experiment/Experiment.h"

#include <iostream.h>

class Base
{
   public:
      virtual void virtFunction() { cout << "here in base" << std::endl:endl; }
      virtual void virtFunction( int ) { 
	 cout << "here in overridden base" << std::endl:endl; }
};

class Derived : public Base
{
   public:
      virtual void virtFunction() { cout << "here in derived" << std::endl:endl; }
};


int main()
{
   Base* base1 = new Base;
   base1->virtFunction();

   Base* base2 = new Derived;
   base2->virtFunction();

   Derived derived;
   derived.virtFunction();
}
