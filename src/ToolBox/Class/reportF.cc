// -*- C++ -*-
//
// Package:     ToolBox
// Module:      reportF
// 
// Description: Interface report_ to report()
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Aug  4 16:38:53 EDT 1998
// $Id: reportF.cc,v 1.5 2000/05/16 15:15:37 bkh Exp $
//
// Revision history
//
// $Log: reportF.cc,v $
// Revision 1.5  2000/05/16 15:15:37  bkh
// Bring up to date with addition of SYSTEM level
//
// Revision 1.4  1999/04/16 13:13:17  bkh
// Fix memory leak by adding deletes
//
// Revision 1.3  1999/02/18 19:00:28  mkl
// added VERIFY SeverityString -- so stupid to keep enums in a separate place in another library
//
// Revision 1.2  1998/09/24 21:52:08  bkh
// Fix argument spec
//
// Revision 1.1  1998/09/24 20:34:41  bkh
// redesigned fortran reporting code, again
//
// Revision 1.2  1998/09/24 14:53:17  bkh
// change to accomodate new severities, no integer argument
//
// Revision 1.1  1998/09/23 21:31:01  bkh
// C++ interface between fortran report_ and C++ report()
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "ToolBox/reportF.h"
#include "Experiment/report.h"

#include <algorithm>

void report_( const FInteger& aSever  ,
	      const FChar*    aCrName ,
	      const FChar*    aMes    ,
	      const FInteger  aClen   ,
	      const FInteger  aMlen    )
{
   char* crName ( new char[ aClen + 1 ] ) ;
   copy( &aCrName[0], &aCrName[ aClen ], crName ) ;
   crName[ aClen ] = '\0' ;
   const string crString ( crName ) ; // calling routine --> "facility"

   Severity sever ( INFO ) ; // default severity is INFO

   if(      70 == aSever ) { sever = SYSTEM    ; }
   else if( 60 == aSever ) { sever = EMERGENCY ; }
   else if( 50 == aSever ) { sever = ALERT     ; }
   else if( 40 == aSever ) { sever = CRITICAL  ; }
   else if( 30 == aSever ) { sever = ERROR     ; }
   else if( 20 == aSever ) { sever = WARNING   ; }
   else if( 10 == aSever ) { sever = NOTICE    ; }
   else if( 0  == aSever ) { sever = INFO      ; }
   else if(-10 == aSever ) { sever = VERIFY    ; }
   else if(-20 == aSever ) { sever = DEBUG     ; }

   const char* pchmess   ( aMes ) ;
   const char* endChmess ( &pchmess[aMlen-1] ) ;
   for( const char* endC ( &pchmess[aMlen-1] ) ; endC >= pchmess ; --endC )
   {
      if( ' ' != *endC )
      {
	 endChmess = 1+endC ;
	 break ;
      }
   }

   const unsigned int len ( ( endChmess - pchmess ) + 1 ) ;
   char* pcMes ( new char[ len ] ) ;
   copy( pchmess, endChmess, pcMes ) ;
   pcMes[ len-1 ] = '\0' ;
   const string chmessString ( pcMes ) ;

   report( sever, crString ) << chmessString << endl ;

   delete [] crName ;
   delete [] pcMes  ;
}

