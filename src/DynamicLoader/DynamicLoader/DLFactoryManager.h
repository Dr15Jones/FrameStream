#if !defined(DYNAMICLOADER_DLFACTORYMANAGER_H)
#define DYNAMICLOADER_DLFACTORYMANAGER_H
// -*- C++ -*-
//
// Package:     <DynamicLoader>
// Module:      DLFactoryManager
// 
/**\class DLFactoryManager DLFactoryManager.h DynamicLoader/DLFactoryManager.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Nov 24 10:34:05 EST 2000
// $Id: DLFactoryManager.h,v 1.2 2003/08/14 16:29:56 cdj Exp $
//
// Revision history
//
// $Log: DLFactoryManager.h,v $
// Revision 1.2  2003/08/14 16:29:56  cdj
// added isLoaded method to DLFactoryManager
//
// Revision 1.1.1.1  2000/11/30 20:51:30  cdj
// imported DynamicLoader source
//

// system include files
#include <map>
#include <string>

// user include files
#include "DynamicLoader/DLSharedObjectHandler.h"

// forward declarations
class DLFactoryBase;
class DLMultiFactoryChooserBase;

template <class T> class DLFactoryManager;
#include "STLUtility/fwd_map.h"

template <class T>
class DLFactoryManagerPtr
{
   public:
      DLFactoryManagerPtr(const string iPaths) : m_ptr(0) { 
	 setPaths(iPaths); grab(); }
      DLFactoryManagerPtr( const DLFactoryManagerPtr<T>& iCopyFrom) : m_ptr(0){
	 grab(); m_ptr= iCopyFrom.m_ptr; }

      ~DLFactoryManagerPtr();

      const DLFactoryManagerPtr<T>& operator=( 
	 const DLFactoryManagerPtr<T>& iRHS) {}

      DLFactoryManager<T>* operator->() { return getPtr(); }
      DLFactoryManager<T>& operator*() { return *(getPtr());}

      const DLFactoryManager<T>* operator->() const { 
	 return getPtr(); }
      const DLFactoryManager<T>& operator*() const { 
	 return *(getPtr());}


   private:
      DLFactoryManager<T>* getPtr() const;
      void setPaths(const string& iPaths );
      void grab() ;
      DLFactoryManager<T>* m_ptr;
};


template <class T>
class DLFactoryManager
{
      // ---------- friend classes and functions ---------------
      friend class DLFactoryManagerPtr<T>;

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------

      // ---------- member functions ---------------------------
      DABoolean add( const string& iName, DLFactoryBase* iFactory );

      DABoolean remove( const string& iName );
      void removeAll();

      DLFactoryBase* fetch( const string& iName,
			    DLMultiFactoryChooserBase& iChooser,
			    string& oShortName );

      // ---------- const member functions ---------------------
      string listAvailable(const string& iPattern ) const;
      string listLoaded() const;
      DABoolean isLoaded(const string& iName ) const;

      string fullName( const string& iName ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------
      static unsigned int& numberOfPtrs() {
	 static unsigned int s_numberOfPtrs = 0;
	 return s_numberOfPtrs;
      }

      static string& paths() {
	 static string s_paths;
	 return s_paths;
      }

      static DLFactoryManager<T>*& instance() { 
	 static DLFactoryManager<T>* s_instance = 0;
	 if( 0 == s_instance ) {
	    s_instance = new DLFactoryManager<T>(paths());
	 }
	 return s_instance;
      }


      static void grab() {
	 ++numberOfPtrs();
      }

      static void release() {
	 --numberOfPtrs();
	 if( 0 == numberOfPtrs()) {
	    delete instance();
	    instance() = 0;
	    paths() = string();
	 }
      }

   private:
      // ---------- Constructors and destructor ----------------
      DLFactoryManager( const string& iPaths ) : m_soh(iPaths) {}
      //virtual ~DLFactoryManager();

      DLFactoryManager( const DLFactoryManager& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DLFactoryManager& operator=( const DLFactoryManager& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      string loadingAsSuperClassMesg( const string& iName ) const;
      string symbolErrorMesg( const string& iName ) const;

      // ---------- data members -------------------------------
      DLSharedObjectHandler m_soh;

      STL_MAP( string, DLFactoryBase *) m_factoryMap;
      // ---------- static data members ------------------------

};

// inline function definitions
template <class T>
inline
void
DLFactoryManagerPtr<T>::grab()
{
   DLFactoryManager<T>::grab();
}

template <class T>
inline
void
DLFactoryManagerPtr<T>::setPaths(const string& iPaths)
{
   DLFactoryManager<T>::paths() = iPaths;
}

template <class T>
inline
DLFactoryManager<T>*
DLFactoryManagerPtr<T>::getPtr() const
{
   if( 0 == m_ptr ) { 
      const_cast<DLFactoryManagerPtr<T>*>(this)->m_ptr = 
	 DLFactoryManager<T>::instance();
   }
   return m_ptr;
}

template <class T>
inline
DLFactoryManagerPtr<T>::~DLFactoryManagerPtr() {
   DLFactoryManager<T>::release();
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DynamicLoader/Template/DLFactoryManager.cc"
//#endif

#endif /* DYNAMICLOADER_DLFACTORYMANAGER_H */
