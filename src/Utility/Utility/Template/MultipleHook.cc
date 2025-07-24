#if !defined(UTILITY_MULTIPLEHOOK_CC)
#define UTILITY_MULTIPLEHOOK_CC

//
//  File:	MultipleHook_T.h
//  Author: 	Simon Patton
//  Contents:	Definitions of the members of `MultipleHook' template class.
//
// $Id: MultipleHook.cc,v 1.14 1998/09/23 19:36:35 mkl Exp $
//
// $Log: MultipleHook.cc,v $
// Revision 1.14  1998/09/23 19:36:35  mkl
// rename kFacilityString in Template/*cc files and take care of static
//
// Revision 1.13  1998/02/06 20:36:24  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.12  1997/09/18 21:35:52  cdj
// changed Boolean to DABoolean
//
// Revision 1.11  1997/09/07 17:55:51  sjp
// Reworked to run with "Experiment" environment
//
// Revision 1.10  1997/09/03 20:06:03  sjp
// Uses CPP macros for STL containers
//
// Revision 1.9  1997/08/27 03:41:13  sjp
// Updated to new name for bug flags
//
// Revision 1.8  1997/07/21 18:37:08  sjp
// put in CPP flags to stop double inclusion
//
// Revision 1.7  1997/07/03 20:18:11  sjp
// New <Package>/<File>.h structure
//
// Revision 1.6  1996/06/21 20:53:20  sjp
// Changed to using STL vector from my deque
//
// Revision 1.5  1996/06/04 16:37:02  sjp
// Converted for using `stack' to `deque'
//
// Revision 1.4  1996/02/20 00:48:16  sjp
// replaced NULL pointer with '0'.
//
// Revision 1.3  1996/01/25 15:47:44  sjp
// Fixed bug on return statement, needed a value after Error.
//
// Revision 1.2  1995/08/18 21:01:57  sjp
// Handled errors with Error class.
// Reformated start of block `{'
//
// Revision 1.1  1995/07/13  15:33:19  sjp
// File moved here from Class/Utility, this appears to be a more
//   natural home.
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>  // For 'exit'
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif

// user include files
#include "Experiment/report.h" // For error report
#include "Utility/SingleHook.h"
#include "Utility/MultipleHook.h"

#include <vector>

//
// constants, enums and typedefs
//

static const char* const kMultipleHookFacilityString 
= "Utility.MultiHook" ;

//
// constructors and destructor
//

//------ Creator -----
//
template <class T>
MultipleHook<T>::MultipleHook( const short aSize ) :
   _hookList( new SingleHook<T>[ aSize ] ) ,
   _size( aSize ) ,
   _last( 0 )
{
   if ( 0 == _hookList ) {
      report( EMERGENCY ,
	      kMultipleHookFacilityString )
		 << "Unable to allocate memory"
		 << std::endl ;
      exit( 1 ) ;
   }
}

//------ Destructor -----
//
template <class T>
MultipleHook<T>::~MultipleHook( void )
{
   delete [] _hookList ;
}


//------ hookUp -----
// Set up the Hook-to-Partner relationship
//
template <class T>
DABoolean	MultipleHook<T>::hookUp( T* pPartner )
{
   if ( ( _last == _size ) ) {
      return ( false ) ;
   }
   return ( _hookList[ _last++ ].hookUp( pPartner ) ) ;
}


//------ unHook -----
// Shut down the Hook-to-Partner relationship
//
template <class T>
DABoolean	MultipleHook<T>::unHook( T* pPartner )
{
   short index = locate( pPartner ) ;
   if ( index == _last ) {
      return ( false ) ;
   }

   if ( !_hookList[ index ].unHook( pPartner ) ) {
      return ( false ) ;
   }

   if ( --_last != index ) {
      T* partnerToMove = _hookList[ _last ].partner() ;
      if ( ! ( ( _hookList[ _last ].unHook( partnerToMove ) ) &&
               ( _hookList[ index ].hookUp( partnerToMove ) ) ) ) {
	 report( EMERGENCY ,
		 kMultipleHookFacilityString )
		    << "Can not cleanly unhook, probably corrupted"
		    << std::endl ;
	 return ( false ) ;
      }
   }
   return ( true ) ;
}


//------ partners -----
// List the partners that are currently hooked
//
template <class T>
void	MultipleHook<T>::partners( std::vector< T* >* pPartnerList ) const
{
   short index = 0 ;
   while ( index < _last ) {
       (*pPartnerList).push_back( _hookList[ index++ ].partner() ) ;
   }
}


//------ hooked -----
// Test the Hook-to-Partner relationship
//

// Test to see if there is any relationship set up
//
template <class T>
DABoolean MultipleHook<T>::hooked( void ) const
{
   return( _hookList[ 0 ].hooked() ) ;
}

// Test to see if the relationship is to this partner
//
template <class T>
DABoolean	MultipleHook<T>::hooked( const T* pPartner ) const
{
   if ( locate( pPartner ) == _last ) {
      return ( false ) ;
   }
   return ( true ) ;
}

//------- locate ------
// For where the first link to a partner is store
//   in the fHookArray
//
template <class T>
short	MultipleHook<T>::locate( const T* pPartner ) const
{
   short index = 0 ;
   while ( ( index < _last ) && ( ! ( _hookList[ index ].hooked( pPartner ) ) ) ) {
       index++ ;
   }
   return ( index ) ;
}

#endif /* UTILITY_MULTIPLEHOOK_CC */
