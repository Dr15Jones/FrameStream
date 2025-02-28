#if !defined(PACKEDDATASTREAMSSTORAGE_PDSSINKCONTROLLER_H)
#define PACKEDDATASTREAMSSTORAGE_PDSSINKCONTROLLER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSSinkController
// 
/**\class PDSSinkController PDSSinkController.h PackedDataStreamsStorage/PDSSinkController.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Sep 13 09:01:11 EDT 2000
// $Id: PDSSinkController.h,v 1.2 2002/11/21 21:17:23 cleo3 Exp $
//
// Revision history
//
// $Log: PDSSinkController.h,v $
// Revision 1.2  2002/11/21 21:17:23  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.1.1.1  2000/09/29 17:49:40  cdj
// imported
//

// system include files
#include "C++Std/fstream.h"

// user include files
#include "DataStorage/DataSinkController.h"
#include "PackedDataStreamsStorage/PDSDataToStore.h"

// forward declarations
class PDSProxyStorer;

class PDSSinkController : public DataSinkController
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSSinkController( const string& iFileName,
			 const Stream::Set& iWriteStreams,
			 const PDSDataToStore& iDataToStore );
      virtual ~PDSSinkController();

      // ---------- member functions ---------------------------
      /// must always store sequentially
      virtual DABoolean mustSequentiallyStore() const {
	 return true; }

      /// Sink ID is the output file name
      virtual string dataSinkID() const {
	 return m_fileName; }

      /// No parameters allowed for PDSSinkController ==> blank
      virtual string parameters() const {
	 return ""; }

      /// Name of the output .pds file
      const string& fileName() const {
	 return m_fileName; }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------
      virtual ProxyStorer* createProxyStorer() const;

   private:
      // ---------- Constructors and destructor ----------------
      PDSSinkController( const PDSSinkController& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSSinkController& operator=( const PDSSinkController& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      string m_fileName ;
      ofstream& m_oStream ;
      PDSProxyStorer* m_proxyStorer;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsStorage/Template/PDSSinkController.cc"
//#endif

#endif /* PACKEDDATASTREAMSSTORAGE_PDSSINKCONTROLLER_H */
