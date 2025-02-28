#if !defined(STORAGEMANAGEMENT_SM_ITERATOR_TRAITS_H)
#define STORAGEMANAGEMENT_SM_ITERATOR_TRAITS_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      sm_iterator_traits
// 
/**\class sm_iterator_traits sm_iterator_traits.h StorageManagement/sm_iterator_traits.h

 Description: provides the iterator traits used by SMFillContents and SMMakeContents

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed May 10 17:56:51 EDT 2000
// $Id: sm_iterator_traits.h,v 1.2 2001/09/07 17:29:25 cleo3 Exp $
//
// Revision history
//
// $Log: sm_iterator_traits.h,v $
// Revision 1.2  2001/09/07 17:29:25  cleo3
// now use NO_ITERATOR_TRAITS_BUG flag
//
// Revision 1.1  2000/05/12 15:44:00  cdj
// made changes to be more C++ standards compliant (needed for g++)
//

// system include files
#include <iterator>

// user include files

// forward declarations
class DummyFriend;

template <class Iterator>
class sm_iterator_traits
{
   public:
      // ---------- constants, enums and typedefs --------------
      typedef typename iterator_traits<Iterator>::value_type value_type;
      typedef Iterator iterator_type;

};

#if !defined(NO_PARTIAL_TEMPLATE_SPECIALIZATION_BUG)

//Need to partially specialize this class for back_insert_iterator because
// back_insert_iterator::value_type is 'void'
template <class Container >
class sm_iterator_traits< back_insert_iterator<Container> >
{
   public:
      // ---------- constants, enums and typedefs --------------
      typedef typename Container::value_type value_type;
      typedef back_insert_iterator<Container> iterator_type;
};
#endif

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/sm_iterator_traits.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SM_ITERATOR_TRAITS_H */
