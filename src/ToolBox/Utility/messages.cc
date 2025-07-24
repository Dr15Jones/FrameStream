#include "ToolBox/Include/MessageLog.h"

#include "Scaffold/Control/Include/Analysis.h"

MessageLog report ;

void Analysis::beginJob( void )
{
   report( DEBUG , "sjp.debug" ) << "debug message" << std::endl ;
   report( INFO , "sjp.info" ) << "info message" << std::endl ;
   report( NOTICE , "sjp.notice" ) << "notice message" << std::endl ;
   report( WARNING , "sjp.warning" ) << "warning message" << std::endl ;
   report( ERROR , "sjp.error" ) << "error message" << std::endl ;
   report( CRITICAL , "sjp.critical" ) << "critical message" << std::endl ;
   report( ALERT , "sjp.alert" ) << "alert message" << std::endl ;
   report( EMERGENCY , "sjp.emergency" ) << "emergency message" << std::endl ;
}
