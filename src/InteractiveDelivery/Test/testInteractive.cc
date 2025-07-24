#include <iostream>
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

   cout << "call Extractor"<<std::endl;
   Extractor( iFrame,
	      eventHeader);

   cout <<" called Extractor"<<std::endl;
   cout <<"Run/Event:"
	<<(*eventHeader).run()
	<<"/"
	<<(*eventHeader).number()
	<<std::endl;

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
      cout <<"Add Data Source error:"<< iAddError <<std::endl;
      exit(1);
   }

   //Set up for interactive control
   InteractiveSource intSource;

   InteractiveSourceBinder intBinder( &intSource );

   if( FrameDeliverer::kAddSourceNoError != 
       (iAddError = frameDeliverer.addSource( intBinder ))){
      cout <<"Add Data Source error:"<< iAddError <<std::endl;
      exit(1);
   }

   FrameDeliverer::AddActiveSourceStatus iActiveError;
   if( FrameDeliverer::kAddActiveSourceNoError != 
       (iActiveError = frameDeliverer.addActiveSource( intBinder))){
      cout <<"Add Active Stream error:"<< iActiveError <<std::endl;
      exit(1);
   }

   DABoolean isDone(false);
   FrameDeliverer::NextStopStatus nextStopStatus;

   while( !isDone ){

      //Prompt user for run event
      DABoolean goodStop(false);
      while( !goodStop ){
	 cout <<"---------------"<<std::endl;
	 cout <<"goto Run Event:";
	 unsigned long run, event;
	 cin >> run >> event;

	 
	 if( intSource.setRunEvent( run, event ) ){
	    goodStop = true;
	 } else {
	    cout <<"Inappropriate values"<<std::endl;
	 }
      }
	 
      
      nextStopStatus = frameDeliverer.gotoNextStop();

      Stream::Type currentStop = frameDeliverer.currentStop();
      cout<<"  status:"<< nextStopStatus << std::endl;
      if( Stream::kNone == currentStop ){
	 isDone = true;
      } else if ( Stream::kBeginRun == currentStop ){
	 cout <<"Begin Run"<<std::endl;
      } else if ( Stream::kEvent == currentStop ){
	 cout <<"Event"<<std::endl;
	 eventProcess( frameDeliverer.currentFrame() );
      } else if ( Stream::kEndRun == currentStop ){
	 cout <<"End Run"<<std::endl;
      } else {
	 cout <<"Unknown Record:"<<currentStop<<std::endl;
	 isDone=true;
      }
   }
      
   cout <<"Next Stop Status ( End of Active Source="
	<<FrameDeliverer::kNextStopReachedEndOfAnActiveSource
	<<"):"
	<<nextStopStatus
	<<std::endl;
      
   return 0;
  
}

