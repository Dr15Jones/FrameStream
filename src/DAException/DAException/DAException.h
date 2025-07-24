#if !defined(DAEXCEPTION_DAEXCEPTION_H)
#define DAEXCEPTION_DAEXCEPTION_H
// -*- C++ -*-
//
// Package:     <DAException>
// Module:      DAException
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
	     << "handling MyException: " << iException.what() << std::endl;
	   // do further handling of exception...
        }
	catch( DAException& iException) {
           report( EMERGENCY, kFacilityString )
	     << "handling DAException: " << iException.what() << std::endl;
	   // do further handling of exception...
        }
	catch( DAExceptionBase& iException) {
           report( EMERGENCY, kFacilityString )
	     << "handling DAException exception: " 
	     << iException.what() << std::endl;
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
	making a copy of the std::string passed in: yes, there is a problem
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
// $Id: DAException.h,v 1.7 2003/04/25 15:19:51 vk Exp $
//
// Revision history
//
// $Log: DAException.h,v $
// Revision 1.7  2003/04/25 15:19:51  vk
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
#include "DAException/DAExceptionBase.h"
#include "DAException/DAExceptionStack.h"

//
// constants, enums and typedefs
//

// forward declarations

class DAException : public DAExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DAException();
      DAException( const char* iMessage, DABoolean iOwnMemory=true );
      virtual ~DAException();

      // copy ctor and assignment op are defined here to allow
      // simpler derivation (no disallowing of copy ctor and ass.op. necessary
      // in derived class)
      DAException( const DAException& iRHS );

      const DAException& operator=( const DAException& iRHS );

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      //! This is what gets printed when exception is caught
      virtual const char* what() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------

      // ---------- assignment operator(s) ---------------------

      // ---------- private member functions -------------------
      void swap( DAException& iFrom );
      
      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const char* m_message;
      DABoolean m_ownMemory;

      // ---------- static data members ------------------------

};

/**\class DAExceptionT DAException.h DAException/DAException.h

        There is a third option: 
	3.) Use the templated Exception "DAExceptionT< "message" >":
	Templating with a "const char*" is a bit tricky. One cannot do:
	
	... throw DAExceptionT< "reason for exception" >();

	because the "const char*" has to be "external". The only way
        is to use an (extern) character array (!) (Neither
        macro-style-const, local, file-static, nor class-static are
        allowed by the standard!) Of course, this restriction makes it
        much less useful. :-((

	extern char message[] = "reason for exception";
	...
        throw DAExceptionT< message >(); 

*/

template< const char* kMessage >
class DAExceptionT : public DAExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DAExceptionT() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      //! This is what gets printed when exception is caught
      virtual const char* what () const { return kMessage; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      DAExceptionT( const DAExceptionT& );

      // ---------- assignment operator(s) ---------------------
      const DAExceptionT& operator=( const DAExceptionT& ); 

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DAException/Template/DAExceptionT.cc"
//#endif

#endif /* DAEXCEPTION_DAEXCEPTION_H */
