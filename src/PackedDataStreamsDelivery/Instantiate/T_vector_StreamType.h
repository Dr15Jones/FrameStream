#if !defined(PACKAGE_T_VECTOR_STREAMTYPE_H)
#define PACKAGE_T_VECTOR_STREAMTYPE_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      T_vector_StreamType
// 
/**\class T_vector_StreamType T_vector_StreamType.h package/T_vector_StreamType.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sun Oct  1 13:32:53 EDT 2000
// $Id: T_vector_StreamType.h,v 1.1 2000/10/02 20:42:25 cdj Exp $
//
// Revision history
//
// $Log: T_vector_StreamType.h,v $
// Revision 1.1  2000/10/02 20:42:25  cdj
// now compiles and links using cxx
//

// system include files

// user include files

// forward declarations

class T_vector_StreamType
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      T_vector_StreamType();
      virtual ~T_vector_StreamType();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      T_vector_StreamType( const T_vector_StreamType& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const T_vector_StreamType& operator=( const T_vector_StreamType& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/T_vector_StreamType.cc"
//#endif

#endif /* PACKAGE_T_VECTOR_STREAMTYPE_H */
