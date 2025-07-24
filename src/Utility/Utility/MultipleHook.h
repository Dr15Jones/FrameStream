#if !defined(MULTIPLEHOOK_H)
#define MULTIPLEHOOK_H

//  File:	MultipleHook.h
//  Author: 	Simon Patton
//  Contents:	Declarations of the members of `MultipleHook' template class.
//
// $Id: MultipleHook.h,v 1.8 1998/02/06 20:36:19 mkl Exp $
//
// $Log: MultipleHook.h,v $
// Revision 1.8  1998/02/06 20:36:19  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.7  1997/09/18 21:35:43  cdj
// changed Boolean to DABoolean
//
// Revision 1.6  1997/09/03 20:05:30  sjp
// Uses CPP macros for STL containers
//
// Revision 1.5  1997/07/11 16:44:28  sjp
// Added INCLUDE_TEMPLATE_DEFINITIONS flag
//
// Revision 1.4  1997/07/03 20:18:10  sjp
// New <Package>/<File>.h structure
//
// Revision 1.3  1996/06/21 20:53:22  sjp
// Changed to using STL vector from my deque
//
// Revision 1.2  1996/06/04 16:37:00  sjp
// Converted for using `stack' to `deque'
//
// Revision 1.1.1.1  1995/06/24 19:17:19  sjp
// Initial example of Ntuple code
//

#include "Utility/Hook.h"

template <class T> class SingleHook ;
#include <vector>

template <class T>
class MultipleHook : public Hook<T>
{
   public:
      
// Creators and Destructors
		MultipleHook( const short aSize ) ;
		~MultipleHook( void ) ;

// Modifiers
      DABoolean	hookUp( T* pPartner ) ;
      DABoolean	unHook( T* pPartner ) ;
 
// Accessors
      void	partners( std::vector< T* >* pPartnerList ) const ;
      DABoolean	hooked( void ) const ;
      DABoolean	hooked( const T* pPartner ) const ;
      
   private:

// Accessors
      short	locate( const T* pPartner ) const ;

// Storage
      SingleHook<T>* _hookList ;
      short _size ;
      short _last ;

} ;

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "Utility/Template/MultipleHook.cc"
#endif

#endif
