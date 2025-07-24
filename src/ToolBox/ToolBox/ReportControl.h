#if !defined(TOOLBOX_REPORTCONTROL_H)
#define TOOLBOX_REPORTCONTROL_H
// -*- C++ -*-
//
// Package:     ToolBox
// Module:      ReportControl
// 
/**\class ReportControl ReportControl.h ToolBox/ReportControl.h

 Description: Provide prescaling, tallying for messages

 Usage:
   
   Sometimes a message occurs so frequently that it is helpful to have 
   it be prescaled so as to not use up CPU time, clog up log files, or 
   scroll useful information off the screen. This class has been 
   written for this purpose. 

   ReportControl is a class that can implement prescaling. In place of 
   the usual report() line, one instantiates a static object of the 
   ReportControl class and then directs output into one of its member
   functions instead of report(). The arguments to the ReportControl 
   constructor set the parameters for the prescaling, including the 
   desired severity and facility string of the message, a preface string, a
   prescaling factor <f>, and a plateau value <p>. Prescaling works as 
   follows: the message is sent to report() the first <f> times, then 
   becomes prescaled by a factor of <f> for the next <f> times, then
   becomes prescaled by another factor of <f>, and so on, until the 
   plateau is reached, after which the message is not sent to report() 
   ever again. For example, if the prescale factor is set to 10 and the
   plateau to 650, one sees invocations of the message for the following 
   occurrences only: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 
   70, 80, 90, 100, 200, 300, 400, 500, 600, and 650. The messages state when
   the prescaling factor is changing, what number invocation of the message 
   is being printed, and when the plateau has been reached. All the 
   information about the prescaling is available from ReportControl
   member functions. 

   Example: 


   #include "ToolBox/ReportControl.h"
   ....

   static ReportControl repCon ( ERROR,
                                 kFacilityString,
                                 "Preface of message: " , // message preface
                                 10,           // geometric prescale factor
                                 1000000  ) ;  // plateau

   if( repCon.nCalls() < repCon.plateau() )
   {
      repcon() << "Here is an error for daqId=" << daqId << std::endl ;
   }


   When the message is not sent to report(), nevertheless an ostream must 
   be returned (report() returns an ostream so that repeated use of the 
   << operator can work just like cout). The solution (from
   dsr) is to send the message into a local, private ostrstream which gets 
   reset every event, and which uses minimal CPU time compared to report().  

*/
//
// Author:      Brian K. Heltsley
// Created:     Thu Dec  2 13:24:04 EST 1999
// $Id: ReportControl.h,v 1.3 2002/08/16 19:34:00 cleo3 Exp $
//
// Revision history
//
// $Log: ReportControl.h,v $
// Revision 1.3  2002/08/16 19:34:00  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.2  1999/12/17 16:51:33  bkh
// Add documentation
//
// Revision 1.1  1999/12/03 15:17:17  bkh
// New class to control prescaling of report messages
//

// system include files
#include <iostream>

// user include files
#include <string>
#include "Utility/Severity.h"

// forward declarations

class ReportControl
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ReportControl( const Severity& aSeverity ,
		     const std::string&   aFacility ,
		     const std::string&   aPreface  ,
		     const UInt32    aFactor   ,
		     const UInt32    aPlateau    );
      virtual ~ReportControl();


      // ---------- member functions ---------------------------

     std::ostream& operator()() ;

      // ---------- const member functions ---------------------

      const Severity& severity() ;
      const std::string&   facility() ;
      const std::string&   preface()  ;
      UInt32          factor()   ;
      UInt32          plateau()  ;

      UInt32          nCalls()   ;
      UInt32          prescale() ;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ReportControl( const ReportControl& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ReportControl& operator=( const ReportControl& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      Severity m_severity ;
      std::string   m_facility ;
      std::string   m_preface  ;
      UInt32   m_factor   ;
      UInt32   m_plateau  ;
	                  
      UInt32   m_nCalls   ;
      UInt32   m_prescale ;

      // ---------- static data members ------------------------

};

#endif /* TOOLBOX_REPORTCONTROL_H */
