//*
// Martin Lohner, July 17, 1998
// The solaris compiler (CC 4.2) doesn't not allow 
// overloading the -> operator for builtin types, but ok for user-defined types

#include "Experiment/Experiment.h"
#include <iostream.h>

class MyClass
{
};

template< class T >
class Handle 
{
   public:
      Handle( T* iMyClass ) : m_myClass( iMyClass ) {}

#if !defined(DEREF_OP_FOR_BUILTIN_TYPES_BUG)
      const T* operator->() const { return m_myClass; }
#endif
      const T& operator*()  const { return *m_myClass; }

   private:
      const T* m_myClass;
};


int main()
{
   Handle< MyClass > handle( new MyClass );
   Handle< int > intHandle( new int( 1 ) );

   #if !defined(DEREF_OP_FOR_BUILTIN_TYPES_BUG)
   cout << intHandle.operator->() << endl;
   #endif
}
