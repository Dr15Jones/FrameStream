#if !defined(PROXYBIND_PROXYBINDABLETEMPLATE_CC)
#define PROXYBIND_PROXYBINDABLETEMPLATE_CC
// -*- C++ -*-
//
// Package:     ProxyBind
// Module:      ProxyBindableTemplate
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sat Feb 27 10:51:27 EST 1999
// $Id: ProxyBindableTemplate.cc,v 1.1.1.1 1999/03/04 19:11:57 cdj Exp $
//
// Revision history
//
// $Log: ProxyBindableTemplate.cc,v $
// Revision 1.1.1.1  1999/03/04 19:11:57  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "ProxyBind/ProxyBindableTemplate.h"
#include "ProxyBind/ProxyBoundActionBase.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//

FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kProxyBindableTemplateReportString = "ProxyBind.ProxyBindableTemplate" ;

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T>
ProxyBindableTemplate<T>::ProxyBindableTemplate() 
   : m_pActions(0)
{
}

// ProxyBindableTemplate::ProxyBindableTemplate( const ProxyBindableTemplate& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

template< class T>
ProxyBindableTemplate<T>::~ProxyBindableTemplate()
{
   if( 0 != m_pActions ) {
      STL_VECTOR(ProxyBoundActionBase*)::iterator itEnd = m_pActions->end();
      for( STL_VECTOR(ProxyBoundActionBase*)::iterator itAction = 
	      m_pActions->begin();
	   itAction != itEnd;
	   ++itAction ) {
	 delete (*itAction );
      }
   }
   delete m_pActions;
}

//
// assignment operators
//
// const ProxyBindableTemplate& ProxyBindableTemplate::operator=( const ProxyBindableTemplate& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
template< class T>
void 
ProxyBindableTemplate<T>::bind( ProxyBoundActionBase* iAction, 
				const Stream::Type& iRecord)
{
   if( 0 == m_pActions ) {
      m_pActions = new STL_VECTOR(ProxyBoundActionBase*);
      if( 0 == m_pActions ) {
	 report(EMERGENCY, kProxyBindableTemplateReportString ) <<"out of memory" << endl;
      }
      m_pActions->reserve(1);
   }
   //should put the action in stream priority order
   m_pActions->push_back( iAction );
}

//
// const member functions
//
template< class T>
const T*
ProxyBindableTemplate<T>::get( const Record& iRecord,  
			    const DataKey& iKey ) const 
{
   if( ! cacheIsValid() ) {

      if( 0 != m_pActions ) {
	 //Loop through our action list
	 STL_VECTOR(ProxyBoundActionBase*)::iterator itEnd = m_pActions->end();
	 for( STL_VECTOR(ProxyBoundActionBase*)::iterator itAction = 
		 m_pActions->begin();
	      itAction != itEnd;
	      ++itAction ) {
	    (*itAction)->execute( iRecord.frame() );
	 }
      }
   }

   //call the base class method to do the main algorithm
   return ProxyTemplate<T>::get( iRecord, iKey );
}
//
// static member functions
//
#endif /* PROXYBIND_PROXYBINDABLETEMPLATE_CC */
