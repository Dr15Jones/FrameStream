#if !defined(JOBCONTROL_FILTERBASE_H)
#define JOBCONTROL_FILTERBASE_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterBase
// 
/**\class FilterBase FilterBase.h JobControl/FilterBase.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Jul 21 16:23:05 EDT 2003
// $Id: Filter.h,v 1.1 2003/09/19 21:26:53 cdj Exp $
//
// Revision history
//
// $Log: Filter.h,v $
// Revision 1.1  2003/09/19 21:26:53  cdj
// first submission of Path code
//

// system include files

// user include files

// forward declarations
namespace JobControlNS {

class FilterBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FilterBase();
      virtual ~FilterBase();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FilterBase( const FilterBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FilterBase& operator=( const FilterBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

} //namespace JobControlNS
#endif /* JOBCONTROL_FILTERBASE_H */
