#include "Experiment/Experiment.h"
template< class T> class Bad;
template< class T> Bad<T> foo(const Bad<T>& );

template <class T>
class Bad
{
      friend Bad<T> foo( const Bad<T>&);

#if defined(TEMPLATE_CLASS_FRIEND_FUNCTION_BUG)
      public:
#endif
      int bar() const { return 1;}
};

template< class T>
Bad<T> 
foo( const Bad<T>& iBad) 
{
   iBad.bar();
   return iBad;
}

template Bad<int> foo(const Bad<int>&);
