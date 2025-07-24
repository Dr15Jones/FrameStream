#if !defined(JOBCONTROL_FILTERCOMPOSITE_H)
#define JOBCONTROL_FILTERCOMPOSITE_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterComposite
// 
/**\class FilterComposite FilterComposite.h JobControl/FilterComposite.h

 Description: Base class for a Filter that holds other Filters

 Usage:
     Does not take ownership of the Filters passed to it (since the
      same filter could be used in multiple FilerComposites)
    
*/
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 13:48:03 EDT 2003
// $Id: FilterComposite.h,v 1.1 2003/09/19 21:26:55 cdj Exp $
//
// Revision history
//
// $Log: FilterComposite.h,v $
// Revision 1.1  2003/09/19 21:26:55  cdj
// first submission of Path code
//

// system include files

// user include files
#include "JobControl/FilterBase.h"
#include <vector>

// forward declarations

namespace JobControlNS {

class FilterComposite : public FilterBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FilterComposite(const std::string& iName);
      //virtual ~FilterComposite();

      // ---------- member functions ---------------------------

      void add(FilterBase* );
      void reset();
      // ---------- const member functions ---------------------
      StreamSet streams() const;

      virtual DABoolean contains(const FilterBase*) const;
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      std::vector<Holder<FilterBase> >& filters() { return m_filters;}

      // ---------- protected const member functions -----------
      const std::vector<Holder<FilterBase> >& filters() const { return m_filters;}

   private:
      // ---------- Constructors and destructor ----------------
      FilterComposite( const FilterComposite& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FilterComposite& operator=( const FilterComposite& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      std::vector<Holder<FilterBase> > m_filters;

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace JobControlNS

#endif /* JOBCONTROL_FILTERCOMPOSITE_H */
