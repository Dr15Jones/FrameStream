#if !defined(DAEXCEPTION_DANOPROXYEXCEPTION_H)
#define DAEXCEPTION_DANOPROXYEXCEPTION_H
// -*- C++ -*-
//
// Package:     DAException
// Module:      DANoProxyException
// 
/**\class DANoProxyException DANoProxyException.h DAException/DANoProxyException.h

 Description: An exception that is thrown whenever proxy was not available
              in the Frame, it is subset of DANoDataException, see more details
              in that class

*/
//
// Author:      Valentine Kouznetsov
// Created:     Wed Apr 23 10:58:26 EDT 2003
// $Id: DANoProxyException.h,v 1.3 2003/09/11 19:04:31 vk Exp $
//
// Revision history
//
// $Log: DANoProxyException.h,v $
// Revision 1.3  2003/09/11 19:04:31  vk
// Replace ends to have the same behaviour on OSF/Solaris/Linux
//
// Revision 1.2  2003/06/02 15:41:12  vk
// Fix to use dependent base member functions, this->x() instead of x()
//
// Revision 1.1  2003/04/25 15:19:55  vk
// Reorginize package, add new stack class
//
//

// system include files
#include <string>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

// user include files
#include "Experiment/Experiment.h"
#include "Experiment/types.h"
#include "Experiment/report.h"

#include "DAException/DANoDataException.h"
#include "DataHandler/RecordMethods.h"
#include "DataHandler/FrameRecordItr.h"
#include "DataHandler/RecordKeyItr.h"
#include "DataHandler/Record.h"

// forward declarations

const char* const kDANoProxyExceptionString = "DAExceptionStack";

template <class T>
class DANoProxyException : public DANoDataException<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DANoProxyException( const Record& iRecord,
			  const DataKey& iDataKey ) :
	 DANoDataException<T>(iRecord.stream(), iDataKey), 
	 m_record( iRecord ),
	 m_message() {}
      //virtual ~DANoProxyException() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual const char* what () const { 

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   strstream m_stream1, m_stream2;
#else
   std::stringstream m_stream1, m_stream2;
#endif
        // Evaluate more precisely what is going on with thrown exception

        // look for proxy in other records
        const Frame& iFrame = m_record.frame();
        Frame::const_iterator fIter = iFrame.begin();
        Frame::const_iterator fIEnd = iFrame.end();
        std::string o_record_proxy = "";
        while( fIter != fIEnd ) 
        { // loop over all records in current frame
          if( fIter->find( this->dataKey() ) )
          { // search if proxy exist in other record
            o_record_proxy = "However this data has been found in ";
            m_stream1 << fIter->stream() << " record." << "\0" << std::flush;
            o_record_proxy+= m_stream1.str();
          }
          fIter++;
        }
        
        // search if proxy has another tags
        Record::const_key_iterator pIter = m_record.begin_key();
        Record::const_key_iterator iEnd  = m_record.end_key();
        std::string sametype_proxy = "";
        while( pIter != iEnd )
        {
          if( pIter->type()  > this->dataKey().type() ) 
          {
            break;
          }
          if( pIter->type() == this->dataKey().type() ) 
          {
            if(!sametype_proxy.size())
            {
              m_stream2 <<"This data type \"" << pIter->type().name()
                        <<"\" exists, but has different tags.\n";
            }
            m_stream2 <<" usage \"" << pIter->usage().value() << "\""
                      <<" production \""
                      << pIter->production().value() << "\""<< "\0" << std::flush;
            sametype_proxy+= m_stream2.str();
          }
          pIter++;
        }
        
        if( m_message.size() == 0 ) {
          std::string& message = 
            const_cast<DANoProxyException<T>*>(this)->m_message;
          message = this->dataTypeMessage();
          
          if(o_record_proxy.size()) {
            message += std::string(" \n ")+o_record_proxy;
            message += std::string(" \n Perhaps you need to change your extract call to use a different record.");
          } else if(sametype_proxy.size()) {
            message += std::string(" \n ")+sametype_proxy;
            message += std::string(" \n Please check your code and/or scripts for correct usage/production tag.");
          } else {
            message += std::string(" \n ")
                    +std::string("Please add a Source or Producer to your job which can deliver this data.");
          }
        }
        return m_message.c_str();
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //DANoProxyException( const DANoProxyException& ) ; //allow default

      // ---------- assignment operator(s) ---------------------
      //const DANoProxyException& operator=( const DANoProxyException& ); // allow default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const Record& m_record;
      std::string m_message;
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DAException/Template/DANoProxyException.cc"
//#endif

#endif /* DAEXCEPTION_DANOPROXYEXCEPTION_H */
