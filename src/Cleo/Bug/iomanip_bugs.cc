// -*- C++ -*-
// Martin Lohner. July 17, 1998
// Bug report: some compilers implement io-manipulators as macros. 
//             Depending which compiler we're talking about, some
//             place a ";" at the end, some others don't.
//
#include "Experiment/Experiment.h"

// system include files
#include <iostream.h>
#include <iomanip.h>

#ifdef NO_STD_NAMESPACE_BUG
#define STD_PREFIX 
#else
#define STD_PREFIX std::
#endif

#if defined(IOMANIP_IS_CPP_MACRO_BUG)
IOMANIPdeclare(double)
#if defined(IOMANIP_MACRO_MISSES_SEMICOLON_BUG)
;
#endif
#else
template class STD_PREFIX smanip<float>;
#endif
