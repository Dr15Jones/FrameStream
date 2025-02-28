#if !defined(JOBCONTROL_FILTERAND_H)
#define JOBCONTROL_FILTERAND_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterAnd
// 
/**\class FilterAnd FilterAnd.h JobControl/FilterAnd.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 14:24:49 EDT 2003
// $Id: FilterAnd.h,v 1.1 2003/09/19 21:26:54 cdj Exp $
//
// Revision history
//
// $Log: FilterAnd.h,v $
// Revision 1.1  2003/09/19 21:26:54  cdj
// first submission of Path code
//

// system include files

// user include files
#include "JobControl/FilterComposite.h"

// forward declarations
namespace JobControlNS {
class FilterAnd : public FilterComposite
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FilterAnd(const string& iName) : FilterComposite(iName) {}
      //virtual ~FilterAnd();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual string description() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual ActionBase::ActionResult implementFilter(Frame&, 
						       const StreamType&);

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FilterAnd( const FilterAnd& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FilterAnd& operator=( const FilterAnd& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace JobControlNS
#endif /* JOBCONTROL_FILTERAND_H */
