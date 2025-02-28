// user include files
#include "DAException/DAExceptionStack.h"

typedef pair<string, int> _vector_contents_;
#include "STLUtility/instantiate_vector.h"

#if defined(AUTO_INSTANTIATE_TEMPLATE_BUG)
template class pair<string,int>;
template class allocator<pair<string,int> >;
#endif
