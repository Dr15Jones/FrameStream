#if !defined(SINGLEHOOK_H)
#define SINGLEHOOK_H

//  File:	SingleHook.h
//  Author: 	Simon Patton
//  Contents:	Declarations of the members of `SingleHook' template class.
//
// $Id: SingleHook.h,v 1.5 1997/09/18 21:35:44 cdj Exp $
//
// $Log: SingleHook.h,v $
// Revision 1.5  1997/09/18 21:35:44  cdj
// changed Boolean to DABoolean
//
// Revision 1.4  1997/07/11 16:44:30  sjp
// Added INCLUDE_TEMPLATE_DEFINITIONS flag
//
// Revision 1.3  1997/07/03 20:18:13  sjp
// New <Package>/<File>.h structure
//
// Revision 1.2  1996/02/27 15:03:21  sjp
// cleaned up include files used
//
// Revision 1.1.1.1  1995/06/24 19:17:19  sjp
// Initial example of Ntuple code
//

#include "Utility/Hook.h"

template <class T>
class SingleHook : public Hook<T>
{
   public:
      
// Creators and Destructors
		SingleHook( void ) ;
		~SingleHook( void ) ;

// Modifiers
      DABoolean	hookUp( T* pPartner ) ;
      DABoolean	unHook( T* pPartner ) ;
 
// Accessors
      T*	partner( void ) const ;
      DABoolean	hooked( void ) const ;
      DABoolean	hooked( const T* pPartner ) const ;
      
   private:

// Storage
      T* _pointerToPartner ;

} ;

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "Utility/Template/SingleHook.cc"
#endif

#endif
