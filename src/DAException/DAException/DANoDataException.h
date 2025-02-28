#if !defined(DAEXCEPTION_DANODATAEXCEPTION_H)
#define DAEXCEPTION_DANODATAEXCEPTION_H
// -*- C++ -*-
//
// Package:     DAException
// Module:      DANoDataException
// 
/**\class DANoDataException DANoDataException.h DAException/DANoDataException.h

 Description: An exception that is thrown whenever data was not available
              in the Frame

 Usage:
    DANoDataException<> is thrown whenever an extract call fails because 
    the type of data being extract was not available in the Frame.

    If your program should continue even if the extract call fails, you should
    catch this exception.

    \code
    try {
      FAItem<DBEventHeader> eventHeader;
      extract( iFrame.record(Stream::kBeginRun), eventHeader );

      report(INFO, kFacilityString ) << "run # " << eventHeader->runNumber()
                                     << "event # " << eventHeader->number()
				     << endl;

    } catch( DANoDataException<FAItem<DBEventHeader>::contents> &iException ) {
      report(WARNING, kFacilityString ) << iException.what() << endl;
    }
      
    \endcode

    To make it easier to catch exceptions, all of the FAXXX types provide
    C preprocessor macros of the form
    \code
       NO_XXX_DATA_EXCEPTION( type )
    \endcode
     which are just shorthand ways of writing
     \code
       DANoDataException<FAXXX<type>::contents>
     \endcode
    E.g.
       \code
       NO_ITEM_DATA_EXCEPTION( DBEventHeader )
       \endcode
       is the same as writing
       \code
       DANoDataException<FAItem<DBEventHeader>::value_type>
       \endcode

    NOTE: DANoDataException<> is only thrown when the data is unavailable. If
      the data should have been available but a problem occured while obtaining
      the data, then a different type of exception will be thrown.

      To catch ALL possible exceptions that can occur from the Data Access 
      system you should catch exceptions of the type DAExceptionBase.
*/
//
// Author:      Chris D Jones
// Created:     Tue Dec  7 09:10:34 EST 1999
// $Id: DANoDataException.h,v 1.2 2003/04/25 15:19:54 vk Exp $
//
// Revision history
//
// $Log: DANoDataException.h,v $
// Revision 1.2  2003/04/25 15:19:54  vk
// Reorginize package, add new stack class
//
// Revision 1.1  1999/12/10 14:02:51  cdj
// added DANoDataException
//

// system include files
#include <string>

// user include files
#include "DAException/DAException.h"
#include "DataHandler/Stream.h"
#include "DataHandler/DurableDataKey.h"
#include "HeteroContainer/HCTypeTagTemplate.h"

// forward declarations

template <class T>
class DANoDataException : public DAExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DANoDataException( const Stream::Type& iStream,
			 const DataKey& iDataKey ) : 
	 m_stream( iStream ),
	 m_dataKey( iDataKey ),
	 m_message() {}
      //virtual ~DANoDataException() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      const DurableDataKey& dataKey() const { return m_dataKey; }
      virtual const char* what () const { 
        if( m_message.size() == 0 ) {
          string& message = 
            const_cast<DANoDataException<T>*>(this)->m_message;
          message = dataTypeMessage();
          message+= string(" \n ")
                 +string(" A proxy for this data exists, but it's unable to deliver the data for this ")
                 +string(m_stream.value())
                 +string(" record.");
        }
	 return m_message.c_str();
      }


      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------
      const string& dataTypeMessage () const { 
	 if( m_dataTypeMessage.size() == 0 ) {
	    //should make m_message mutable
	    string& message = 
	       const_cast<DANoDataException<T>*>(this)->m_dataTypeMessage;

	    message = string("No data of type ") 
	       +string("\"")
	         +string(HCTypeTagTemplate<T,DataKey>::className()) 
	       +string("\" ")
	       +string("\"")
	         +string(m_dataKey.usage().value() )
	       +string("\" ")
	       +string("\"")
	         +string(m_dataKey.production().value() )
	       +string("\" ")
	       +string("in Record ")
	       +string(m_stream.value());
	 }
	 return m_dataTypeMessage;
      }

   private:
      // ---------- Constructors and destructor ----------------
      //DANoDataException( const DANoDataException& ) ; //allow default

      // ---------- assignment operator(s) ---------------------
      //const DANoDataException& operator=( const DANoDataException& ); // allow default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Stream::Type m_stream;
      DurableDataKey m_dataKey;
      string m_message;
      string m_dataTypeMessage;
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DAException/Template/DANoDataException.cc"
//#endif

#endif /* DAEXCEPTION_DANODATAEXCEPTION_H */
