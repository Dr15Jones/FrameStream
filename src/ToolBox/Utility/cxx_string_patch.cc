#include "C++Std/iostream.h"

#include "ToolBox/Include/bug7_deccxx.h"
#if !defined(BUG7__DECCXX)
#  include <string>
#else
#  include <String.h>
   typedef String string ;
#endif

int main()
{
   string nullfac( "." ) ;
   string fac( ".one.two..three.four.five" ) ;

   while ( fac.length() > 0 ) {
      cout << fac << endl ;
#if !defined(BUG7__DECCXX)
      size_t dot = fac.rfind(nullfac);
      if (dot != string::npos) {
	 fac.resize(dot);
      }
#else
      size_t npos = -1 ;
      size_t nullfacLength = nullfac.length() ;
      size_t dot ;
      if ( fac.length() < nullfacLength ) {
	 dot = npos ;
      }
      else {
	 dot = fac.length() - nullfacLength ;
      }
      while ( ( dot != npos ) &&
	      ( fac( dot , nullfacLength ) != nullfac ) ) {
	 --dot ;
      }
      if ( dot != npos ) {
	 fac = fac( 0 , dot ) ;
      }
#endif
      else {
	 // last chance match  -- will be shortened to 0 on the next
	 // iteration (probably too clever for its own good)
	 fac = nullfac;
      }
   }

   return ( 0 ) ;
}
