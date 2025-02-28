#if !defined(UTILITY_SINGLEHOOK_CC)
#define UTILITY_SINGLEHOOK_CC

//
//  File:	SingleHook_T.h
//  Author: 	Simon Patton
//  Contents:	Definitions of the members of `SingleHook' template class.
//
// $Id: SingleHook.cc,v 1.7 1997/09/18 21:35:54 cdj Exp $
//
// $Log: SingleHook.cc,v $
// Revision 1.7  1997/09/18 21:35:54  cdj
// changed Boolean to DABoolean
//
// Revision 1.6  1997/07/21 18:37:10  sjp
// put in CPP flags to stop double inclusion
//
// Revision 1.5  1997/07/03 20:18:15  sjp
// New <Package>/<File>.h structure
//
// Revision 1.4  1996/02/27 20:12:42  sjp
// changed NULL to zeros
//
// Revision 1.3  1996/02/27 15:03:19  sjp
// cleaned up include files used
//
// Revision 1.2  1995/08/18 21:02:53  sjp
// Reformated opening block `{'
//
// Revision 1.1  1995/07/13  15:33:17  sjp
// File moved here from Class/Utility, this appears to be a more
//   natural home.
//

#include "Experiment/Experiment.h"

#include "Utility/SingleHook.h"

//------ Creator -----
//
template <class T>
SingleHook<T>::SingleHook( void ) : _pointerToPartner( 0 )
{
}

//------ Destructor -----
//
template <class T>
SingleHook<T>::~SingleHook( void )
{
}


//------ hookUp -----
// Set up the Hook-to-Partner relationship
//
template <class T>
DABoolean	SingleHook<T>::hookUp( T* pPartner )
{
   if ( ( hooked() ) || ( 0 == pPartner ) ) {
      return ( false ) ;
   }
   _pointerToPartner = pPartner ;
   return ( true ) ;
}


//------ unHook -----
// Shut down the Hook-to-Partner relationship
//
template <class T>
DABoolean	SingleHook<T>::unHook( T* pPartner )
{
   if ( !hooked( pPartner ) ) {
      return ( false ) ;
   }
   _pointerToPartner = 0 ;
   return ( true ) ;
}


//------ partner -----
// Retrun the address of the Hooked partner
//
template <class T>
T*	SingleHook<T>::partner( void ) const
{
   return ( _pointerToPartner ) ;
}


//------ hooked -----
// Test the Hook-to-Partner relationship
//

// Test to see if there is any relationship set up
//
template <class T>
DABoolean SingleHook<T>::hooked( void ) const 
{
   return( 0 != _pointerToPartner ) ;
}

// Test to see if the relationship is to this partner
//
template <class T>
DABoolean	SingleHook<T>::hooked( const T* pPartner ) const
{
   return ( _pointerToPartner == pPartner ) ;
}


#endif /* UTILITY_SINGLEHOOK_CC */
