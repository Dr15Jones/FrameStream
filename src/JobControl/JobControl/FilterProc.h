#if !defined(JOBCONTROL_FILTERPROC_H)
#define JOBCONTROL_FILTERPROC_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterProc
// 
/**\class FilterProc FilterProc.h JobControl/FilterProc.h

 Description: A filter that wraps around one Processor

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Jul 28 13:27:07 EDT 2003
// $Id: FilterProc.h,v 1.1 2003/09/19 21:26:56 cdj Exp $
//
// Revision history
//
// $Log: FilterProc.h,v $
// Revision 1.1  2003/09/19 21:26:56  cdj
// first submission of Path code
//

// system include files

// user include files
#include "JobControl/FilterBase.h"

// forward declarations
class Processor;

namespace JobControlNS {
class FilterProc : public FilterBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FilterProc(Processor* );
      //virtual ~FilterProc();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual StreamSet streams() const;

      const Processor* processor() const { return m_proc; }
      
      virtual std::string description() const ;
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      ActionBase::ActionResult implementFilter(Frame&, const StreamType&);

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FilterProc( const FilterProc& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FilterProc& operator=( const FilterProc& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Processor* m_proc;

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace JobControlNS
#endif /* JOBCONTROL_FILTERPROC_H */
