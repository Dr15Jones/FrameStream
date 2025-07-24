#if !defined(PACKEDDATASTREAMSDELIVERY_PDSTYPEUNPACKINGINFO_H)
#define PACKEDDATASTREAMSDELIVERY_PDSTYPEUNPACKINGINFO_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSTypeUnpackingInfo
// 
/**\class PDSTypeUnpackingInfo PDSTypeUnpackingInfo.h PackedDataStreamsDelivery/PDSTypeUnpackingInfo.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Tue Sep 19 13:27:00 EDT 2000
// $Id: PDSTypeUnpackingInfo.h,v 1.5 2003/01/24 19:51:43 cdj Exp $
//
// Revision history
//
// $Log: PDSTypeUnpackingInfo.h,v $
// Revision 1.5  2003/01/24 19:51:43  cdj
// use UnixFileHandleStream when reading gzipped files
//
// Revision 1.4  2002/04/04 19:13:37  cdj
// speed optimization: use SMPackerBase instead of PDSPackerBase when reading back
//
// Revision 1.2  2001/04/10 19:48:14  cdj
// can now store strings
//
// Revision 1.1.1.1  2000/09/29 17:48:04  cdj
// imported
//

// system include files
#include <vector>

// user include files

// forward declarations
class PDSPackerBase;
class PDSPackerFactory;
class SMPackerBase;
#include <vector>
#include "PackedDataStreamsFormat/pds_packing_enums.h"

class PDSTypeUnpackingInfo
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      struct TypePacker {
         SMPackerBase* m_packer;
         PDSPacking::Types m_type;
         TypePacker( PDSPacking::Types iType = PDSPacking::kNumberOfTypes,
                     SMPackerBase* iPacker = reinterpret_cast<SMPackerBase*>(0) ) :
            m_packer(iPacker),
            m_type(iType) {}
      };            
      // ---------- Constructors and destructor ----------------
      PDSTypeUnpackingInfo();
      virtual ~PDSTypeUnpackingInfo();

      // ---------- member functions ---------------------------
      void readPackingInfo( const UInt32*& ioHeader,
			    DABoolean iSwappedBytes );

      // ---------- const member functions ---------------------
      unsigned int version() const { return m_version; }

      PDSPackerBase* packer( unsigned int iIndex ) const {
	 return m_packers[iIndex];
      }

      TypePacker* begin() {
         return &(*(m_typePackers.begin()));
      }
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      std::vector<PDSPackerBase*>& packers() { return m_packers;}
      std::vector<TypePacker>& typePackers() { return m_typePackers;}

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //PDSTypeUnpackingInfo( const PDSTypeUnpackingInfo& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const PDSTypeUnpackingInfo& operator=( const PDSTypeUnpackingInfo& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      static PDSPackerFactory& packerFactory();
      // ---------- data members -------------------------------
      unsigned int m_version;
      std::vector<PDSPackerBase*> m_packers;
      std::vector<TypePacker> m_typePackers;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSTypeUnpackingInfo.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSTYPEUNPACKINGINFO_H */
