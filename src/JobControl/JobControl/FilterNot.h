#if !defined(JOBCONTROL_FILTERNOT_H)
#define JOBCONTROL_FILTERNOT_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterNot
// 
/**\class FilterNot FilterNot.h JobControl/FilterNot.h

 Description: A filter that returns the 'not' of the Filter it holds

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 13:27:07 EDT 2003
// $Id: FilterNot.h,v 1.1 2003/09/19 21:26:55 cdj Exp $
//
// Revision history
//
// $Log: FilterNot.h,v $
// Revision 1.1  2003/09/19 21:26:55  cdj
// first submission of Path code
//

// system include files

// user include files
#include "JobControl/FilterBase.h"

// forward declarations
class Processor;

namespace JobControlNS {
class FilterNot : public FilterBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FilterNot(const string& iName, FilterBase* );
      //virtual ~FilterNot();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual StreamSet streams() const;

      const FilterBase* filter() const { return m_filter.get(); }

      virtual DABoolean contains(const FilterBase*) const;
      
      virtual string description() const ;
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      ActionBase::ActionResult implementFilter(Frame&, const StreamType&);

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FilterNot( const FilterNot& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FilterNot& operator=( const FilterNot& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Holder<FilterBase> m_filter;

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace JobControlNS
#endif /* JOBCONTROL_FILTERNOT_H */
