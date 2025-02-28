#if !defined(HOOK_H)
#define HOOK_H

//  File:	Hook.h
//  Author: 	Simon Patton
//  Contents:	Declarations of the members of `Hook' abstract template class.
//
// $Id: Hook.h,v 1.4 1997/09/18 21:35:42 cdj Exp $
//
// $Log: Hook.h,v $
// Revision 1.4  1997/09/18 21:35:42  cdj
// changed Boolean to DABoolean
//
// Revision 1.3  1997/07/03 20:18:05  sjp
// New <Package>/<File>.h structure
//
// Revision 1.2  1996/02/27 15:03:23  sjp
// cleaned up include files used
//
// Revision 1.1.1.1  1995/06/24 19:17:19  sjp
// Initial example of Ntuple code
//

template <class T>
class Hook
{
   public:
      
// Creators and Destructors
		Hook( void ) { } ;
      virtual	~Hook( void ) { } ;

// Modifiers
      virtual	DABoolean	hookUp( T* pPartner ) = 0 ;
      virtual	DABoolean	unHook( T* pPartner ) = 0 ;
 
// Accessors
      virtual	DABoolean	hooked( void ) const = 0 ;
      virtual	DABoolean	hooked( const T* pPartner ) const = 0 ;
      
} ;


#endif
