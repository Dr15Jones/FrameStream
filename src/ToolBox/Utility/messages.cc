#include "ToolBox/Include/MessageLog.h"

#include "Scaffold/Control/Include/Analysis.h"

MessageLog report ;

void Analysis::beginJob( void )
{
   report( DEBUG , "sjp.debug" ) << "debug message" << endl ;
   report( INFO , "sjp.info" ) << "info message" << endl ;
   report( NOTICE , "sjp.notice" ) << "notice message" << endl ;
   report( WARNING , "sjp.warning" ) << "warning message" << endl ;
   report( ERROR , "sjp.error" ) << "error message" << endl ;
   report( CRITICAL , "sjp.critical" ) << "critical message" << endl ;
   report( ALERT , "sjp.alert" ) << "alert message" << endl ;
   report( EMERGENCY , "sjp.emergency" ) << "emergency message" << endl ;
}
