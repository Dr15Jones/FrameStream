#if !defined(DYNAMICLOADER_DLSYMBOLNOTFOUNDEXCEPTION_H)
#define DYNAMICLOADER_DLSYMBOLNOTFOUNDEXCEPTION_H
// -*- C++ -*-
//
// Package:     <DynamicLoader>
// Module:      DLSymbolNotFoundException
// 
/**\class DLSymbolNotFoundException DLSymbolNotFoundException.h DynamicLoader/DLSymbolNotFoundException.h

 Description: Thrown if the attempt to dynamically load a symbol fails.

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Nov 20 13:48:33 EST 2000
// $Id: DLSymbolNotFoundException.h,v 1.1.1.1 2000/11/30 20:51:30 cdj Exp $
//
// Revision history
//
// $Log: DLSymbolNotFoundException.h,v $
// Revision 1.1.1.1  2000/11/30 20:51:30  cdj
// imported DynamicLoader source
//

// system include files

// user include files
#include "DAException/DAException.h"

// forward declarations

class DLSymbolNotFoundException : public DAException
{

   public:
      // ---------- Constructors and destructor ----------------
      DLSymbolNotFoundException( const char* iError ) :
	 DAException(iError) {}

};

#endif /* DYNAMICLOADER_DLSYMBOLNOTFOUNDEXCEPTION_H */
