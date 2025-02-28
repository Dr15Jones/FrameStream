#if !defined(COMMANDPATTERN_EXCEPTIONBASE_H)
#define COMMANDPATTERN_EXCEPTIONBASE_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      ExceptionBase
// 
/**\class ExceptionBase ExceptionBase.h CommandPattern/Keyword/ExceptionBase.h

 Description: Base class for exceptions thrown while processing keywords

 Usage:
    Can only inherit from this class since 'what' is not overwritten from 
    DAExceptionBase.

*/
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 16:20:40 EDT 2003
// $Id: ExceptionBase.h,v 1.1 2003/09/19 20:45:41 cdj Exp $
//
// Revision history
//
// $Log: ExceptionBase.h,v $
// Revision 1.1  2003/09/19 20:45:41  cdj
// first submission
//

// system include files

// user include files
#include "DAException/DAExceptionBase.h"

// forward declarations

namespace CommandPattern
{
namespace Keyword
{
class ExceptionBase : public DAExceptionBase
{
   public:
      // ---------- Constructors and destructor ----------------
      ExceptionBase() {}
      //virtual ~ExceptionBase();
};

} //namespace Keyword
} //namespace CommandPattern
#endif /* COMMANDPATTERN_EXCEPTIONBASE_H */
