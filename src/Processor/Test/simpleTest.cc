#if !defined(FILENAME_ONLY) /* relative path includes */
#include "Processor/Test/MyProcessor.h"
#include "Processor/Include/ActionBase.h"
#include "DataDelivery/Include/Stream.h"
#include "DataDelivery/Include/Frame.h"

#else /* filename-only includes */
#include "MyProcessor.h"
#include "ActionBase.h"
#include "Stream.h"
#include "Frame.h"
#endif /* filename-only includes */

#include <algorithm>
#include <map>

int main( void )
{
   MyProcessor myProcessor;
   
   map< Stream::Type, ActionBase*, less<Stream::Type > > 
      actionMap( myProcessor.actions() );
   
   ActionBase* eventAction( (*(actionMap.find( "event" ))).second );
   ActionBase* beginRunAction( (*(actionMap.find( "beginrun" ))).second );
   
   Frame frame;
   (*beginRunAction)(frame);
   (*eventAction)(frame);
   (*eventAction)(frame);
   (*beginRunAction)(frame);
   (*eventAction)(frame);
   
   return 0;
}
