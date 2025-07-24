// ******************************************************** 
// stand-alone testing program for the DataDelivery system
// without Suez!
// ******************************************************** 

#include <iostream.h>
#include <stdlib.h>  // required for 'exit'
#include <String.h>

#include "ToolBox/Include/functions.h" // for report

// user include files
#include "SyncFrame.h"
#include "Switchboard/Include/Frame.h"
#include "Switchboard/Include/EventRecord.h"
#include "Switchboard/Include/DataElement.h"
#include "Switchboard/Include/DataTable.h"

#include <vector>

#include "FrameDeliverer.h"
#include "KarpDataBinder.h"



//------ anal1 -----
//
void anal1( Frame& )
{
}


//------ anal2 -----
//
void anal2( Frame& )
{
}





//------ anal3 -----
//
void anal3( Frame& iFrame )
{
   const EventRecord& event = iFrame.event();

   if( event.contains( EventElements::kPionFit ) ){
      const DataElement& pionFit = event.dataElement( EventElements::kPionFit);

      DataTable pionFitTable( pionFit.size() );
      if( pionFit.fillTable( pionFitTable) ){
	 cout <<"Number of Pions:"<<pionFitTable.height()<<std::endl; 
      } else {
	 //table didn't fill
	 cout << "PionTable not filled"<<std::endl;
      }
   } else {
      //Event record doesn't have pion fit
      cout << "Event record doesn't have pion fit"<<std::endl;
   }

}

//------ anal4 -----
//
void anal4( Frame& )
{
}


//------ anal5 -----
//
void anal5( Frame& )
{
//   clearSpeciesTable() ;
}


// -----------------------------------------------------------------
// main routine

int main(int argc, char *argv[]){

   FrameDeliverer FD;
      
   //Bind the source to the stream
   AsciiBinder
   KarpDataBinder karpDataBinder = KarpDataBinder( hostname, port,
						   schema, dbname,
						   numComponents, 
						   Stream::kBeginRun |
						   Stream::kEvent |
						   Stream::kEndRun,
						   true );

   //Open the source requested
   FrameDeliverer::AddDataSourceError iError;
      
   if( ! FD.addDataSource( karpDataBinder, iError) ){
      switch(iError){
	 case FrameDeliverer::kInvalidStopsForSource:
	 cout << "Source can't goto those stops"<<std::endl;
	 break;
	 case FrameDeliverer::kSourceDidntLikeInfo:
	 cout << "Couldn't open data source "<<std::endl;
	 break;
	 case FrameDeliverer::kConflictingStopResponsibility:
	 cout << "Another source already goes to that stop"<<std::endl;
	 break;
      }
      exit(1);
   }
      
      
   cout <<"Opened data stream"<<std::endl;
   anal1() ;
      
   FD.setActiveStreams( Stream::kBeginRun |
      Stream::kEvent |
      Stream::kEndRun 
      );
      
   //Before running, check to see if we have sources for all the stops we
   //  requested.
   if(FD.needMoreSources()){
      cout<<"Need more sources"<<std::endl;
      exit(0);
   }
      
   // request a certain SynchronizationValue (run, event here)
   unsigned long run, evnt;
   cout << "Input first run, evnt" << std::endl;
   cin >> run >> evnt;
   if( ! FD.synchronizeSources( SyncValue( run, evnt ) ) ) {
      report(EMERGENCY) << "---couldn't synchronize Sources---" << std::endl;
      exit(1);
   }


   cout <<"Starting loop"<<std::endl;
      
   int isDone = 0;
   while(! isDone ){
      Stream::Type currentRecord = FD.nextStop( ) ;
      switch( currentRecord){
	 case Stream::kNone:
	    report( EMERGENCY ) <<"---Done---"<<std::endl;
	    isDone = 1;
	    break;
	 case Stream::kBeginRun:
	    cout <<"---BeginRun---"<<std::endl;
            // anal2(FD.currentFrame());
	    FD.currentFrame();
	    break;
	 case Stream::kEvent:
	    cout <<"---Event---"<<std::endl;
	    // anal3(FD.currentFrame()) ;
	    FD.currentFrame();
	    break;
	 case Stream::kEndRun:
	    cout <<"---EndRun---"<<std::endl;
	    break;
	 default:
	    report( EMERGENCY )<<"Unknown record type:"<<currentRecord<<std::endl;
	    isDone = 1;
	    break;
      }
      if(!isDone){
	 char wait;
	 cout<<"Next Record?";
	 cin >>wait;
	 if('n'== wait){
	    isDone = 1;
	 }
      }
	 
   }
   anal5() ;
      
   FrameDeliverer::RemoveDataSourcesError iCloseError;
   if( ! FD.removeDataSources(Stream::kEvent,
			      iCloseError) ){
      switch(iCloseError){
	 case FrameDeliverer::kCloseStopsNotValid:
	 cout << "CloseDataSource: Stop to be deactivated was not active" <<std::endl;
	 break;
      }
      exit(1);
   }
      
}
  

#if 0
//////////////////////////////////////////////////////////////////////


DataSourceManager *dataSourceManager = 
(*dataBinder).createDataSourceManager();

if( !(*dataSourceManager).setRecordsToRetrieve( Stream::kBeginRun |
						Stream::kEvent |
						Stream::kEndRun ) ) {
   cout << "couldn\'t set setRecordsToRetrieve" << std::endl;
}

// try out synchronization
cout << "trying out Synchronization feature" << std::endl;
cout << "input run/event number (have to be the same for now)" << std::endl;
int runn, eventn;
cin >> runn >> eventn;

if( !(*dataSourceManager).synchronizeSource( SyncValue( runn, eventn ) ) ) {
   cerr << "couldn't synchronize" << std::endl;
   exit(-1);
}

int isDone = 0;
while(! isDone ){
   Stream::Type typeOfNextRecord = 
      (*dataSourceManager).gotoNextRecord( Stream::kEvent |
					   Stream::kEndRun );
   switch( typeOfNextRecord ) {
      case Stream::kNone:
      cout <<"---Done---"<<std::endl;
      isDone = 1;
      break;
      case Stream::kBeginRun:
      cout <<"---BeginRun---"<<std::endl;
      break;
      case Stream::kEvent:
      cout <<"---Event---"<<std::endl;
      break;
      case Stream::kEndRun:
      cout <<"---EndRun---"<<std::endl;
      break;
      default:
      cout << "Unknown record type:" << typeOfNextRecord << std::endl;
      isDone = 1;
      break;
   }

   if(!isDone){

      // now look at the records for data
      Record *record=(*dataSourceManager).createRecord( typeOfNextRecord );
      cout << (*record).identifier() << ": [";
      
      // first component is Stream::Type; skip!
      for(int i=1; i<iNumComponents; ++i) {
	 int* comp = (int*)(*record).component(i);
	 if(comp == 0) continue;
	 for(int j=0; j<3; ++j) {
	    cout << " ";
	    cout << comp[j];
	 }
      }
      cout << " ]\n" << std::flush;
      //delete record; // eventually have to do something smarter here


      // read more records?
      char wait;
      cout<<"Next Record?";
      cin >>wait;
      if('n'== wait){
	 isDone = 1;
      }
   }
      

}

delete dataSourceManager;
delete dataBinder;
      
}
#endif

