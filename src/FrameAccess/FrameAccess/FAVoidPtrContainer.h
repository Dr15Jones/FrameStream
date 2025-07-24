#if !defined(FRAMEACCESS_FAVOIDPTRCONTAINER_H)
#define FRAMEACCESS_FAVOIDPTRCONTAINER_H
// -*- C++ -*-
//
// Package:     <FrameAccess>
// Module:      FAVoidPtrContainer
// 
/**\class FAVoidPtrContainer FAVoidPtrContainer.h FrameAccess/FAVoidPtrContainer.h

 Description: The underlying container used by FAPtrTable.

 Usage:
    No one should use this class directly.

    This class uses a map if the template class is not an integral type 
    (i.e. not a char, short, int, etc) and a vector if it is.  The vector
    is a speed and size optimization.

*/
//
// Author:      Chris D Jones
// Created:     Mon Oct 30 13:11:19 EST 2000
// $Id: FAVoidPtrContainer.h,v 1.8 2004/02/13 20:39:12 cdj Exp $
//
// Revision history
//
// $Log: FAVoidPtrContainer.h,v $
// Revision 1.8  2004/02/13 20:39:12  cdj
// fixed bug which only occurs for signed integer identifiers where the first inserted element has a negative identifier
//
// Revision 1.7  2002/06/04 18:31:55  cleo3
// changed SUNCC cpp switch to AUTO_INSTANTIATE_TEMPLATE_BUG
//
// Revision 1.6  2001/09/07 17:47:20  cleo3
// added typename
//
// Revision 1.5  2001/04/17 01:08:35  cleo3
// modified to compile under linux
//
// Revision 1.4  2001/02/16 20:48:58  ajm36
// improved findIteratorJustBefore, added a standalone test
//
// Revision 1.3  2001/01/02 22:22:17  cdj
// bug fixes:
//  - calling find on an empty list no longer segfaults
//  - no longer allows you to insert an item with a duplicate identifier
// - insert now has exact same return type as map::insert
//
// Revision 1.2  2000/12/27 19:06:05  cdj
// added workaround for Solaris automatic template instantiation bug
//
// Revision 1.1  2000/11/02 21:30:48  cdj
// first submission
//

// system include files
#include <map>
#include <vector>
#include <algorithm>

// user include files

// forward declarations
#include <map>
#include <vector>

template <class T>
class FAVoidPtrContainer : public std::map<T,void*>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef typename std::map<T,void*>::const_iterator const_iterator;
      typedef typename std::map<T,void*>::iterator iterator;

      // ---------- Constructors and destructor ----------------
      FAVoidPtrContainer() {}
      //virtual ~FAVoidPtrContainer();

      // ---------- member functions ---------------------------
      ///does nothing, just used to match vector interface
      void reserve( unsigned long ) {}

      // ---------- const member functions ---------------------

      const_iterator find( const T& iIdentifier ) {
	 return std::map<T,void*>::find( iIdentifier ); }
      
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //FAVoidPtrContainer( const FAVoidPtrContainer& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const FAVoidPtrContainer& operator=( const FAVoidPtrContainer& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};


/**\class FAVoidPtrIntegralIdContainer FAVoidPtrContainer.h FrameAccess/FAVoidPtrContainer.h

 Description: The base class used by the FAVoidPtrContainer integral type 
   template specializations

 Usage:
    No one should use this class directly.

    The class checks to see if it holds a contiguous group of identifiers (e.g. 8,9,10,11) and if it does it uses an O(1) find algorithm. 

*/
template <class Integral>
struct FAVoidPtrIntegralIdPairFirstCompare {
      DABoolean operator() ( const Integral& iLHS,
			     const Integral& iRHS ) {
	 return ( iLHS.first < iRHS.first );
      }
};

template<class T>
class FAVoidPtrIntegralIdContainer : public std::vector< std::pair<T,void *> >
{
      
   public:
      typedef std::vector< std::pair<T,void*> > ParentClass;
      typedef typename ParentClass::value_type value_type;
      typedef typename ParentClass::iterator iterator;
      typedef typename ParentClass::const_iterator const_iterator;
      
      typedef FAVoidPtrIntegralIdPairFirstCompare<value_type> PairFirstCompare;


      // ---------- Constructors and destructor ----------------
      FAVoidPtrIntegralIdContainer() : m_isIndexable(true) {}

      // ---------- member functions ---------------------------
      iterator insert( iterator, 
		       const value_type& iValueType ) {
	 return insert( iValueType ).first;
      }

      iterator insert( const_iterator, const value_type& iValueType ) {
	 return insert( iValueType ).first;
      }

      STD_PREFIX pair<iterator, DABoolean> 
      insert( const value_type& iValueType ) {
	 STD_PREFIX pair<iterator,DABoolean> returnValue;
	 returnValue.second = true;
	 if( this->empty() ) {
	    m_isIndexable = true;
	    push_back( iValueType );
	    returnValue.first =  this->begin();
	 } else {
	    if(m_isIndexable) {
	       if ( this->front().first + this->size() == iValueType.first ) {
		  //we just have to put this at the end
		  push_back( iValueType );
		  returnValue.first = (this->end() - 1);
	       } else if( this->front().first == iValueType.first + 1 ) {
		  //we just have to put this at the beginning
		     ParentClass::insert( this->begin(), iValueType );
		     returnValue.first = this->begin();
	       } else if( iValueType.first >= this->front().first &&
			  iValueType.first - this->front().first < this->size() ) {
		  //the value already exists
		  returnValue.first = this->begin() + iValueType.first - this->front().first;
		  returnValue.second = false;
	       } else {
		  //the list is no longer indexable
		  m_isIndexable = false;
		  if( iValueType.first < this->front().first ) {
		     //put it at the beginning of the list
		     returnValue.first = ParentClass::insert(this->begin(), 
							     iValueType );
		  } else {
		     //put it at the end of the list
		     returnValue.first = ParentClass::insert(this->end(), 
							     iValueType );
		  }
	       }
	    } else {
	       iterator it = findIteratorJustBefore( iValueType.first );
	       if( it != this->end()  &&
		   it->first == iValueType.first ) {
		  //already in the list
		  returnValue.first = it;
		  returnValue.second = false;
	       } else {
		  returnValue.first = ParentClass::insert(it, iValueType );
		  //cast is used to avoid a compiler warning
		  if( this->size() == 
		      static_cast<unsigned int>(this->back().first - this->front().first 
						+ 1) ) {
		     m_isIndexable = true;
		  }
	       }
	    }
	 }
	 return returnValue;
      }


      const_iterator find( const T& iIdentifier ) {
	 if( this->empty() ) {
	    return this->end();
	 }
	 if( m_isIndexable) {
	    //Can just jump to the proper entry in the vector
	    if( this->front().first <= iIdentifier &&
		this->back().first >= iIdentifier ) {
	       return this->begin() + (iIdentifier - this->front().first );
	    } 
	 }

	 //need to search the vector for the identifier
	 iterator result = lower_bound( this->begin(), this->end(), 
					value_type(iIdentifier, 
						   static_cast<void*>(0)),
					PairFirstCompare() );
	 if( result != this->end() &&
	     result->first == iIdentifier ) {
	    //make sure that we actually found the item we want
	    // (lower_bound returns where the object 'should be')
	    return result;
	 }

	 return this->end();
      }

  private:
      // ---------- private member functions -------------------
      iterator findIteratorJustBefore( T iIdentifier ) {
         //Look for the easy cases first.  If neither works, do a binary
         //search on the sorted vector
         if(iIdentifier > this->back().first)
         {
            return this->end();
         }
         if(iIdentifier < this->front().first)
         {
            return this->begin();
         }
         return lower_bound( this->begin(), this->end(), 
                             value_type(iIdentifier, 
                                        static_cast<void*>(0)),
                             PairFirstCompare() );
      }

      // ---------- data members -------------------------------
      DABoolean m_isIndexable;
};


//This macro makes it easy to explicitly specialize FAVoidPtrContainer
//  when T is an integral type
#if !defined(AUTO_INSTANTIATE_TEMPLATE_BUG)
#define SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(__type__) \
template<> class FAVoidPtrContainer<__type__> : \
             public FAVoidPtrIntegralIdContainer<__type__> \
             { public: FAVoidPtrContainer() {} };
#else /* Need to work around an instantiation bug on Solaris */
#define SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(__type__) \
template class pair<__type__, void*>; \
template<> class FAVoidPtrContainer<__type__> : \
             public FAVoidPtrIntegralIdContainer<__type__> \
             { public: FAVoidPtrContainer() {} };
#endif
SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(char)
SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(short)
SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(int)
SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(long)

SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(unsigned char)
SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(unsigned short)
SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(unsigned int)
SPECIALIZE_INTEGRAL_FAVOIDPTRCONTAINER(unsigned long)


// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "FrameAccess/Template/FAVoidPtrContainer.cc"
//#endif

#endif /* FRAMEACCESS_FAVOIDPTRCONTAINER_H */
