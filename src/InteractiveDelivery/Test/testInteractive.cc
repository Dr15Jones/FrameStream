#include "C++Std/iostream.h"
#include "DataHandler/Include/Stream.h"
#include "DataDelivery/Include/FrameDeliverer.h"
#include "DataHandler/Include/StreamSet.h"


#include "DataHandler/Include/DHItem.h"
#include "DataHandler/Include/Frame.h"
#include "DataHandler/Include/Extractor.h"

#include "CleoDB/Include/DBEventHeader.h"
#include "CleoDB/Include/DBPhotonFit.h"

#include "AsciiDelivery/Include/AsciiSourceBinder.h"
#include "InteractiveDelivery/Include/InteractiveSource.h"
#include "InteractiveDelivery/Include/InteractiveSourceBinder.h"
void eventProcess( const Frame& iFrame)
{
   DHItem< DBEventHeader > eventHeader;

   cout << "call Extractor"<<endl;
   Extractor( iFrame,
	      eventHeader);

   cout <<" called Extractor"<<endl;
   cout <<"Run/Event:"
	<<(*eventHeader).run()
	<<"/"
	<<(*eventHeader).number()
	<<endl;

   return;
}

int main( void )
{
   char fileName[256];
   FrameDeliverer frameDeliverer;


   FrameDeliverer::AddSourceStatus iAddError;

   Stream::Set readRunEvent;
   readRunEvent.insert( Stream::kBeginRun);
   readRunEvent.insert( Stream::kEvent );
   cout <<"ASCII Source File Name :";
   cin >> fileName;

   AsciiSourceBinder asciiRunEventBinder( fileName,
					  readRunEvent);

   if( FrameDeliverer::kAddSourceNoError != 
       (iAddError = frameDeliverer.addSource( asciiRunEventBinder))){
      cout <<"Add Data Source error:"<< iAddError <<endl;
      exit(1);
   }

   //Set up for interactive control
   InteractiveSource intSource;

   InteractiveSourceBinder intBinder( &intSource );

   if( FrameDeliverer::kAddSourceNoError != 
       (iAddError = frameDeliverer.addSource( intBinder ))){
      cout <<"Add Data Source error:"<< iAddError <<endl;
      exit(1);
   }

   FrameDeliverer::AddActiveSourceStatus iActiveError;
   if( FrameDeliverer::kAddActiveSourceNoError != 
       (iActiveError = frameDeliverer.addActiveSource( intBinder))){
      cout <<"Add Active Stream error:"<< iActiveError <<endl;
      exit(1);
   }

   DABoolean isDone(false);
   FrameDeliverer::NextStopStatus nextStopStatus;

   while( !isDone ){

      //Prompt user for run event
      DABoolean goodStop(false);
      while( !goodStop ){
	 cout <<"---------------"<<endl;
	 cout <<"goto Run Event:";
	 unsigned long run, event;
	 cin >> run >> event;

	 
	 if( intSource.setRunEvent( run, event ) ){
	    goodStop = true;
	 } else {
	    cout <<"Inappropriate values"<<endl;
	 }
      }
	 
      
      nextStopStatus = frameDeliverer.gotoNextStop();

      Stream::Type currentStop = frameDeliverer.currentStop();
      cout<<"  status:"<< nextStopStatus << endl;
      if( Stream::kNone == currentStop ){
	 isDone = true;
      } else if ( Stream::kBeginRun == currentStop ){
	 cout <<"Begin Run"<<endl;
      } else if ( Stream::kEvent == currentStop ){
	 cout <<"Event"<<endl;
	 eventProcess( frameDeliverer.currentFrame() );
      } else if ( Stream::kEndRun == currentStop ){
	 cout <<"End Run"<<endl;
      } else {
	 cout <<"Unknown Record:"<<currentStop<<endl;
	 isDone=true;
      }
   }
      
   cout <<"Next Stop Status ( End of Active Source="
	<<FrameDeliverer::kNextStopReachedEndOfAnActiveSource
	<<"):"
	<<nextStopStatus
	<<endl;
      
   return 0;
  
}

