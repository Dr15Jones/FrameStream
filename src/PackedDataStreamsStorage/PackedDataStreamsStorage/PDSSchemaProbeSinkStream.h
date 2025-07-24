#if !defined(PACKEDDATASTREAMSSTORAGE_PDSSCHEMAPROBESINKSTREAM_H)
#define PACKEDDATASTREAMSSTORAGE_PDSSCHEMAPROBESINKSTREAM_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSSchemaProbeSinkStream
// 
/**\class PDSSchemaProbeSinkStream PDSSchemaProbeSinkStream.h PackedDataStreamsStorage/PDSSchemaProbeSinkStream.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Thu Sep 14 15:43:59 EDT 2000
// $Id: PDSSchemaProbeSinkStream.h,v 1.1.1.1 2000/09/29 17:49:40 cdj Exp $
//
// Revision history
//
// $Log: PDSSchemaProbeSinkStream.h,v $
// Revision 1.1.1.1  2000/09/29 17:49:40  cdj
// imported
//

// system include files
#include <set>

// user include files
#include "StorageManagement/SMSinkStream.h"
#include "PackedDataStreamsStorage/PDSProxyStorer.h"

// forward declarations
#include <set>

class PDSSchemaProbeSinkStream : public SMSinkStream
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSSchemaProbeSinkStream();
      virtual ~PDSSchemaProbeSinkStream();

      // ---------- member functions ---------------------------
      virtual void put( const char * iFieldName, char );
      virtual void put( const char * iFieldName, short );
      virtual void put( const char * iFieldName, int );
      virtual void put( const char * iFieldName, long );

      virtual void put( const char * iFieldName, unsigned char );
      virtual void put( const char * iFieldName, unsigned short );
      virtual void put( const char * iFieldName, unsigned int );
      virtual void put( const char * iFieldName, unsigned long );

      virtual void put( const char * iFieldName, float );
      virtual void put( const char * iFieldName, double );
      virtual void put( const char * iFieldName, const std::string& );

      virtual void put( const char * iFieldName, const SMContentsBase& );

      virtual void beginObject( const TypeTag& );
      virtual void endObject();


      void setPackerContainer( std::vector<PDSPackerBase*>* iContainer ) {
	 m_packers = iContainer; }

      void clearSubtypes();

      // ---------- const member functions ---------------------
      const std::set<TypeTag>& subtypesFound() const {
	 return m_subtypes; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSSchemaProbeSinkStream( const PDSSchemaProbeSinkStream& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSSchemaProbeSinkStream& operator=( const PDSSchemaProbeSinkStream& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      std::set<TypeTag> m_subtypes;
      std::vector<PDSPackerBase*>* m_packers;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsStorage/Template/PDSSchemaProbeSinkStream.cc"
//#endif

#endif /* PACKEDDATASTREAMSSTORAGE_PDSSCHEMAPROBESINKSTREAM_H */
