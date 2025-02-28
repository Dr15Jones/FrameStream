#if !defined(PROXYBIND_PROXYBOUNDMETHODACTION_H)
#define PROXYBIND_PROXYBOUNDMETHODACTION_H
// -*- C++ -*-
//
// Package:     ProxyBind
// Module:      ProxyBoundMethodAction
// 
// Description: implementation of ProxyBoundActionBase that calls a method
//               function of ProxyType to perform the Algorithm
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Sat Feb 27 10:14:17 EST 1999
// $Id: ProxyBoundMethodAction.h,v 1.1.1.1 1999/03/04 19:11:57 cdj Exp $
//
// Revision history
//
// $Log: ProxyBoundMethodAction.h,v $
// Revision 1.1.1.1  1999/03/04 19:11:57  cdj
// first submission
//

// system include files

// user include files
#include "ProxyBind/ProxyBoundActionBase.h"

// forward declarations

template< class ProxyType >
class ProxyBoundMethodAction : public ProxyBoundActionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ProxyBoundMethodAction( const Stream::Type& iStream,
			      void (ProxyType::*iMethod)( const Record& ),
			      ProxyType* iProxy) :
	 ProxyBoundActionBase( iStream ),
	 m_proxy( iProxy ),
	 m_method( iMethod ) {}
      //virtual ~ProxyBoundMethodAction();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      void implementExecute( const Record& iRecord ) {
	 (m_proxy->*m_method)( iRecord ); }

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ProxyBoundMethodAction(); // stop default
      ProxyBoundMethodAction( const ProxyBoundMethodAction& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ProxyBoundMethodAction& operator=( const ProxyBoundMethodAction& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      ProxyType* m_proxy;
      void (ProxyType::*m_method)( const Record& );

};
// cpp macro for creating the 'bind' method for a Proxy
#define PROXY_BIND_METHOD( ProxyName ) \
void ProxyName ::bind( void( ProxyName ::*iMethod)( const Record& ), \
                       const Stream::Type& iStream ) { \
  ProxyBindableTemplate< ProxyName ::value_type >:: \
   bind( new ProxyBoundMethodAction< ProxyName >( iStream, iMethod, this ), \
	 iStream ); } \
template class ProxyBoundMethodAction< ProxyName >;
#endif /* PROXYBIND_PROXYBOUNDMETHODACTION_H */
