#if !defined(HISTOGRAMINTERFACE_HIBINARYOPBASE_H)
#define HISTOGRAMINTERFACE_HIBINARYOPBASE_H
// -*- C++ -*-
//
// Package:     HistogramInterface
// Module:      HIBinaryOpBase
// 
/**\class HIBinaryOpBase HIBinaryOpBase.h package/HIBinaryOpBase.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Aren Jansen
// Created:     Fri Jan 21 11:55:21 EST 2000
// $Id: HIBinaryOpBase.h,v 1.2 2003/01/17 20:34:34 cdj Exp $
//
// Revision history
//
// $Log: HIBinaryOpBase.h,v $
// Revision 1.2  2003/01/17 20:34:34  cdj
// use namespace to avoid using template math operations with non-histogram code
//
// Revision 1.1  2000/02/15 16:16:44  cdj
// arithmetic operations now use expression templates
//

// system include files

// user include files

// forward declarations
#if !defined(NO_KOENIG_LOOKUP_RULE_BUG)
namespace HistogramInterface {
#endif

class HIBinaryOpBase
{
      // ---------- friend classes and functions ---------------
  
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      HIBinaryOpBase() {}
      //virtual ~HIBinaryOpBase();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual float execute( unsigned int channel ) const = 0;
      virtual float executeError( unsigned int channel ) const = 0;
      virtual void setScalar( const float iScale ) const = 0;
      virtual const float scalar() const  = 0;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      // HIBinaryOpBase( const HIBinaryOpBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const HIBinaryOpBase& operator=( const HIBinaryOpBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#if !defined(NO_KOENIG_LOOKUP_RULE_BUG)
};
#endif

#endif /* HISTOGRAMINTERFACE_HIBINARYOPBASE_H */
