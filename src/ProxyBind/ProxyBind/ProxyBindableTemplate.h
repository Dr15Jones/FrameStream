#if !defined(PROXYBIND_PROXYBINDABLETEMPLATE_H)
#define PROXYBIND_PROXYBINDABLETEMPLATE_H
// -*- C++ -*-
//
// Package:     ProxyBind
// Module:      ProxyBindableTemplate
// 
// Description: Proxy class that handles the case where the calculation in
//               your Proxy is dependent on data in another Record.
//
// Usage:
//    This is a special type of Proxy for the case where the data your
//    creating depends on auxilliary data that lives in a seperate Record.
//    In particular, you want to perform a computationally intensive
//    calculation using the auxilliary data, and you only want to do the
//    calculation when the auxilliary data has changed since the last
//    time you did the calculation.  
//
//    To handle this case, you write a new ProxyBoundActionBase object
//    that does your calculation.  Then when someone asks for the Proxy's 
//    data, the Proxy checks to see if the auxilliary data has changed
//    (i.e. is there a new Record) and if so, it calls calls
//    ProxyBoundActionBase::execute.  Then after all the necessary calculations
//    have been performed, the Proxy calls faultHandler(...).
//    
//
// Author:      Chris D Jones
// Created:     Sat Feb 27 10:13:47 EST 1999
// $Id: ProxyBindableTemplate.h,v 1.1.1.1 1999/03/04 19:11:56 cdj Exp $
//
// Revision history
//
// $Log: ProxyBindableTemplate.h,v $
// Revision 1.1.1.1  1999/03/04 19:11:56  cdj
// first submission
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "DataHandler/Stream.h"

// forward declarations
class ProxyBoundActionBase;
#include <vector>

template< class T >
class ProxyBindableTemplate : public ProxyTemplate< T >
{
      // ---------- friend classes and functions ---------------
      typedef T value_type;

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ProxyBindableTemplate();
      virtual ~ProxyBindableTemplate();

      // ---------- member functions ---------------------------
      void bind( ProxyBoundActionBase* iAction, const Stream::Type& iRecord);

      // ---------- const member functions ---------------------
      virtual const T* get( const Record& iRecord,  
			    const DataKey& iKey ) const ;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void invalidateCache( void ) = 0;
      virtual const T* faultHandler( const Record& iRecord , 
				     const DataKey& iKey )=0;

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ProxyBindableTemplate( const ProxyBindableTemplate& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ProxyBindableTemplate& operator=( const ProxyBindableTemplate& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      std::vector<ProxyBoundActionBase*>* m_pActions;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "ProxyBind/Template/ProxyBindableTemplate.cc"
#endif

#endif /* PROXYBIND_PROXYBINDABLETEMPLATE_H */
