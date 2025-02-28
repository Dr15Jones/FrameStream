#if !defined(PACKEDDATASTREAMSDELIVERY_PDSGUNZIPIFSTREAMHOLDER_H)
#define PACKEDDATASTREAMSDELIVERY_PDSGUNZIPIFSTREAMHOLDER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSGunzipIFStreamHolder
// 
/**\class PDSGunzipIFStreamHolder PDSGunzipIFStreamHolder.h PackedDataStreamsDelivery/PDSGunzipIFStreamHolder.h

 Description: Owns the system pipe used to read gzipped files

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Sep 16 12:59:40 EDT 2002
// $Id: PDSGunzipIFStreamHolder.h,v 1.5 2003/01/24 19:51:42 cdj Exp $
//
// Revision history
//
// $Log: PDSGunzipIFStreamHolder.h,v $
// Revision 1.5  2003/01/24 19:51:42  cdj
// use UnixFileHandleStream when reading gzipped files
//
// Revision 1.4  2002/11/21 21:16:59  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.3  2002/10/17 20:51:26  cdj
// made gzip file reading work on Solaris 8
//
// Revision 1.2  2002/09/19 19:32:18  cdj
// bug fix: will now read .pds extension files
//
// Revision 1.1  2002/09/19 18:06:38  cdj
// can now read gzipped files with extension .pds.gz
//

// system include files
#include <stdio.h>
#include "C++Std/UnixFileHandleStream.h"
#include <memory>

// user include files

// forward declarations

class PDSGunzipIFStreamHolder
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSGunzipIFStreamHolder( const string& iFileName ) :
	 m_fileHandle(NULL),
	 m_errorOccurred(false)
      {
	 unsigned int kSizeOfExtension = 3;
	 if( iFileName.size() > kSizeOfExtension) {
	    if( iFileName.substr(iFileName.size()-kSizeOfExtension,
				 kSizeOfExtension)
		== ".gz") {
	       m_command = string("gunzip -c ")+ iFileName;
	       m_fileHandle = popen(m_command.c_str(), "r");
	       if( NULL == m_fileHandle) {
		  m_errorOccurred=true;
		  return;
	       }
	       
	       m_stream= auto_ptr<istream>(new UnixFileHandleStream(fileNumber()));
	    }
	 }
	 if( NULL==m_fileHandle ){
	    ifstream* tStream = new ifstream(iFileName.c_str());
	    m_stream = auto_ptr<istream>(tStream);
	    
	    if(
#if defined(NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG)
	       ! (*(*tStream).rdbuf()).is_open()
#else
	       ! (*tStream).is_open()
#endif
	       ) {
	       m_errorOccurred = true;
	    }
	 }
      }
      ~PDSGunzipIFStreamHolder() {
	 if( NULL != m_fileHandle) {
	    //need to call this before pclose to avoid deadlocks
	    // (see popen's man page)
	    fflush(m_fileHandle);
	    pclose(m_fileHandle);
	 }
      }

      // ---------- member functions ---------------------------
      void resetToBeginning() {
	 if( m_fileHandle !=NULL ) {
	    m_stream = auto_ptr<istream>(static_cast<istream*>(0));
	    //get a new pipe
	    fflush(m_fileHandle);
	    pclose(m_fileHandle);
	    m_fileHandle = popen(m_command.c_str(), "r");
	    if( NULL == m_fileHandle) {
	       m_errorOccurred=true;
	    }
	    m_stream= auto_ptr<istream>(new UnixFileHandleStream(fileNumber()));
	 } else {
	    (*m_stream).seekg(0);
	    if(!(*m_stream)) {
	       m_errorOccurred = true;
	    }
	 }
      }

      istream& stream() { return *m_stream;}

      // ---------- const member functions ---------------------
      DABoolean errorOccurred() const {
	 return m_errorOccurred;
      }
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSGunzipIFStreamHolder( const PDSGunzipIFStreamHolder& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSGunzipIFStreamHolder& operator=( const PDSGunzipIFStreamHolder& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      int fileNumber() const {
	 return fileno(m_fileHandle);
      }

      // ---------- data members -------------------------------
      FILE* m_fileHandle;
      DABoolean m_errorOccurred;
      string m_command;
      auto_ptr<istream> m_stream;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSGunzipIFStreamHolder.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSGUNZIPIFSTREAMHOLDER_H */
