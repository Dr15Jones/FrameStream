#if !defined(PACKEDDATASTREAMSFORMAT_PDSPACKERTEMPLATE_H)
#define PACKEDDATASTREAMSFORMAT_PDSPACKERTEMPLATE_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSPackerTemplate
// 
/**\class PDSPackerTemplate PDSPackerTemplate.h PackedDataStreamsFormat/PDSPackerTemplate.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 19:34:02 EDT 2000
// $Id: PDSPackerTemplate.h,v 1.2 2002/04/04 19:12:30 cdj Exp $
//
// Revision history
//
// $Log: PDSPackerTemplate.h,v $
// Revision 1.2  2002/04/04 19:12:30  cdj
// speed optimization: use SMPackerBase instead of PDSPackerBase when reading back
//
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files

#include "PackedDataStreamsFormat/PDSPackerBase.h"

// forward declarations

template <class T>
class PDSPackerTemplate : public PDSPackerBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSPackerTemplate() {}
      //virtual ~PDSPackerTemplate();

      // ---------- member functions ---------------------------
      virtual SMPackerTemplate<T>& packer() = 0;

      SMPackerBase* smPacker() { return &(packer()); }
      // ---------- const member functions ---------------------
      PDSPacking::Types type() const {
	 return s_type;
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSPackerTemplate( const PDSPackerTemplate& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSPackerTemplate& operator=( const PDSPackerTemplate& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      static PDSPacking::Types s_type;

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSPackerTemplate.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSPACKERTEMPLATE_H */
