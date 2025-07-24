#include <iostream>
#if !defined(FILENAME_ONLY) /* relative path includes */
#include "ToolBox/Include/bug7_deccxx.h"
#include "ToolBox/Include/bug2_mwerks.h"
#else /* filename-only includes */
#include "bug7_deccxx.h"
#include "bug2_mwerks.h"
#endif /* filename-only includes */

#if !defined(BUG7__DECCXX)
#  include <string>
#if defined(BUG2__MWERKS__)
#  include <string.h>
inline DABoolean operator<( const string& aLhs , const string aRhs )
{
   return ( 0 > strcmp( aLhs.c_str() , aRhs.c_str() ) ) ;
}
#endif
#else
#  include <String.h>
   typedef String string ;
#endif

class One
{
   public:
      typedef int Identifier ;

      One( const Identifier& aId ) ;

      Identifier identifier() const ;

   private:
      Identifier m_id ;
} ;

One::One( const Identifier& aId ) :
   m_id( aId )
{
}

One::Identifier One::identifier() const
{
   return ( m_id ) ;
}


class Two
{
   public:
      typedef string Identifier ;

      Two( const Identifier& aId ) ;

      Identifier identifier() const ;

   private:
      Identifier m_id ;
} ;

Two::Two( const Identifier& aId ) :
   m_id( aId )
{
}

Two::Identifier Two::identifier() const
{
   return ( m_id ) ;
}

int main( void)
{
   One a( 2 ) ;
   Two b( "Alan" ) ;
   
   cout << "a " << a.identifier() << " b " << b.identifier() << std::endl ;
}
