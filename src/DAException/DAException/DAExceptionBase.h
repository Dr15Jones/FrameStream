#if !defined(DAEXCEPTION_DAEXCEPTIONBASE_H)
#define DAEXCEPTION_DAEXCEPTIONBASE_H
// -*- C++ -*-
//
// Package:     <DAException>
// Module:      DAExceptionBase
// 
/**\class DAException DAException.h DAException/DAException.h

 Description: Base class for all (Offline) Exceptions

 Usage:
        This interface allows several uses:
	1.) Derive from DAException and override the "what()" method:

\code
	// in header
	class MyException : public DAException {
	    public:
	       virtual const char* what() const { return "reason for exception"; }
        };

	// in code: some condition has failed
	throw MyException();
\endcode

	2.) Either use DAException directly or via inheritance, but pass
	    message into ctor:

\code
	// in header (only necessary if want to distinguish exception by type)
	class MyException : public DAException { 
	    public:
	       MyException( const char* iMessage ) : DAException( iMessage ) {}
        };

	// in code: some condition has failed
	throw MyException( "reason for exception" );
	// or
        throw DAException( "reason for exception", false ); // don't own memory
\endcode

	In any case, one *should* catch the exception in calling code
	that can handle this type of exception; you may distinguish
	between different types of exceptions, and if so, start with
	the most derived type first!  If nothing catches it, SuezMain
	will finally catch it!

\code
	// in calling code
	try {
	   // do something
        }
	catch( MyException& iException) {
           report( EMERGENCY, kFacilityString )
	     << "handling MyException: " << iException.what() << endl;
	   // do further handling of exception...
        }
	catch( DAException& iException) {
           report( EMERGENCY, kFacilityString )
	     << "handling DAException: " << iException.what() << endl;
	   // do further handling of exception...
        }
	catch( DAExceptionBase& iException) {
           report( EMERGENCY, kFacilityString )
	     << "handling DAException exception: " 
	     << iException.what() << endl;
	   // do further handling of exception...
        }
\endcode

	When inheriting from DAException, it is probably best to use the 
	"natural" namespace of the class that will handle the exception, 
	to protect namespace pollution:
	
\code
	class MyHandlingClass
	{
	   public:
	      class MyException : public DAException {
	      ...
	      };
           ...
        };
\endcode

	For all those people out there worrying about DAException
	making a copy of the string passed in: yes, there is a problem
	with an out-of-memory exception occuring when the DAException is 
	actively being handled. Well, first of all, while an exception is active,
	another exception being thrown would terminate the program!
	Also, according to Stroustrup, "The C++ Programming Language", 3rd ed.,
	page 386:

	"Note that exception operations do not themselves throw
	exceptions. In particular, this implise that throwing a
	standard library exception doesn't cause a bad-alloc
	exception. The exception-handling mechanism keeps a bit of
	memory to itself for holding exceptions (possibly on the
	stack). Naturally, it is possible to write code that
	eventually consumes all memory in the system, thus forcing a
	failure."

 */
//
// Author:      Martin Lohner
// Created:     Tue Nov 30 11:36:14 EST 1999
// $Id: DAExceptionBase.h,v 1.1 2003/04/25 15:19:52 vk Exp $
//
// Revision history
//
// $Log: DAExceptionBase.h,v $
// Revision 1.1  2003/04/25 15:19:52  vk
// Reorginize package, add new stack class
//
// Revision 1.6  2002/06/12 19:31:14  cleo3
// now take a const char* instead of char*
//
// Revision 1.5  2001/03/02 17:42:09  cdj
// need to cast const of const char* input so we can assign it to our char*
//
// Revision 1.4  2001/03/01 17:36:08  cdj
// fixed bug which happened when we don't own the memory
//
// Revision 1.3  2000/09/18 22:37:02  mkl
// need to allocate strlen+1
//
// Revision 1.2  1999/12/18 16:35:25  mkl
// doxygenized code pieces
//
// Revision 1.1.1.1  1999/12/06 16:05:13  mkl
// reimport due to name change: CleoException-->DAException
//
//

// system include files
#include <stdexcept>
#include <stdlib.h>

// user include files
#include "DAException/DAExceptionStack.h"

//
// constants, enums and typedefs
//

// forward declarations

// "exception" not supported on all platforms: don't bother for now
// class DAException : public exception
class DAExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DAExceptionBase();
      virtual ~DAExceptionBase() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      //! This is what gets printed when exception is caught
      virtual const char* what () const =0;

      // Information about stack
      const string exceptionStack () const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      // allow default
      //DAExceptionBase( const DAExceptionBase& );

      // ---------- assignment operator(s) ---------------------
      // allow default
      //const DAExceptionBase& operator=( const DAExceptionBase& ); 

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      unsigned int m_size;

      // ---------- static data members ------------------------

};

#endif /* DAEXCEPTION_DAEXCEPTIONBASE_H */
