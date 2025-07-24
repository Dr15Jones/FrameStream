// user include files
#include "DAException/DAExceptionStack.h"

typedef std::pair<string, int> _vector_contents_;
#include "STLUtility/instantiate_vector.h"

#if defined(AUTO_INSTANTIATE_TEMPLATE_BUG)
template class std::pair<string,int>;
template class allocator<std::pair<string,int> >;
#endif
