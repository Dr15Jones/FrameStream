#if !defined(JOBCONTROL_FILTERBASE_H)
#define JOBCONTROL_FILTERBASE_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FilterBase
// 
/**\class FilterBase FilterBase.h JobControl/FilterBase.h

 Description: Base class for Filters used by Paths

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Jul 21 16:23:05 EDT 2003
// $Id: FilterBase.h,v 1.1 2003/09/19 21:26:54 cdj Exp $
//
// Revision history
//
// $Log: FilterBase.h,v $
// Revision 1.1  2003/09/19 21:26:54  cdj
// first submission of Path code
//

// system include files
#include <string>

// user include files
#include "Processor/ActionBase.h"

// forward declarations
class StreamSet;
class Frame;
class StreamType;

namespace JobControlNS {

class FilterBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FilterBase(const std::string& iName);
      virtual ~FilterBase();

      // ---------- member functions ---------------------------
      /** will cache the result from implementFilter */
      ActionBase::ActionResult filter(Frame&, const StreamType&) ;

      virtual void reset();

      void addRef() {
         ++m_refCount;
      }
      void removeRef();
      
      void setName(const std::string& iName) { m_name = iName;}
      // ---------- const member functions ---------------------
      virtual StreamSet streams() const = 0;

      virtual DABoolean contains(const FilterBase*) const;

      std::string name() const {return m_name.size()?m_name:description();}
      
      virtual std::string description() const = 0;
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual ActionBase::ActionResult implementFilter(Frame&, 
						       const StreamType&) =0;

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FilterBase( const FilterBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FilterBase& operator=( const FilterBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      DABoolean m_filtered;
      ActionBase::ActionResult m_result;
      std::string m_name;

      unsigned int m_refCount;
      // ---------- static data members ------------------------

};

template <class T>
class Holder
{
  public:
   Holder() : m_ptr(0) {}
   Holder(T* iFilter) : m_ptr(iFilter) {
      if(0 != m_ptr ) {
         m_ptr->addRef();
      }
   }
   ~Holder() {
      if(0 != m_ptr) {
         m_ptr->removeRef();
      }
   }
   Holder(const Holder<T>& iHolder) : m_ptr(iHolder.m_ptr) {
      if( 0 != m_ptr ) {
         m_ptr->addRef();
      }
   }
   const Holder& operator=(const Holder<T>& iRHS ) {
      Holder<T> temp(iRHS);
      swap(temp);
      return *this;
   }
   
   void swap(Holder<T>& iOther) {
      T* temp = m_ptr;
      m_ptr = iOther.m_ptr;
      iOther.m_ptr = temp;
   }
   
   T* operator->() const {
      return m_ptr;
   }
   T& operator*() const {
      return *m_ptr;
   }
   T* get() const {
      return m_ptr;
   }
  private:
   T* m_ptr;
};
// inline function definitions

} //namespace JobControlNS
#endif /* JOBCONTROL_FILTERBASE_H */
