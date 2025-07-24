#if !defined(JOBCONTROL_FILTERXOR_H)
#define JOBCONTROL_FILTERXOR_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterXOr
// 
/**\class FilterXOr FilterXOr.h JobControl/FilterXOr.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 14:24:49 EDT 2003
// $Id: FilterXOr.h,v 1.1 2003/09/19 21:26:56 cdj Exp $
//
// Revision history
//
// $Log: FilterXOr.h,v $
// Revision 1.1  2003/09/19 21:26:56  cdj
// first submission of Path code
//

// system include files

// user include files
#include "JobControl/FilterComposite.h"

// forward declarations
namespace JobControlNS {
class FilterXOr : public FilterComposite
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FilterXOr(const std::string& iName) : FilterComposite(iName) {}
      //virtual ~FilterXOr();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual std::string description() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual ActionBase::ActionResult implementFilter(Frame&, 
						       const StreamType&);

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FilterXOr( const FilterXOr& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FilterXOr& operator=( const FilterXOr& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace JobControlNS
#endif /* JOBCONTROL_FILTERXOR_H */
