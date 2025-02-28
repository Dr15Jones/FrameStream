// mkl: this is a bug with the solaris CC 4.2 compiler
#include "Experiment/Experiment.h"

template< class T >
class MyClass
{
   public:
#if !defined(RETURN_TYPE_FROM_DEREFERENCING_OPERATOR_FOR_BUILTIN_TYPES_BUG)
      const T* operator->() const { return m_item;  } // not ok
#endif
      const T& operator*() const  { return *m_item; } // ok
   private:
      const T* m_item;
};

template class MyClass< int >;
