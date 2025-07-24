#if !defined(COMMANDPATTERN_LOADERMULTIFACTORYCHOOSER_H)
#define COMMANDPATTERN_LOADERMULTIFACTORYCHOOSER_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      LoaderMultiFactoryChooser
// 
/**\class LoaderMultiFactoryChooser LoaderMultiFactoryChooser.h CommandPattern/LoaderMultiFactoryChooser.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Nov 29 16:03:23 EST 2000
// $Id: LoaderMultiFactoryChooser.h,v 1.1 2000/12/01 20:23:23 cdj Exp $
//
// Revision history
//
// $Log: LoaderMultiFactoryChooser.h,v $
// Revision 1.1  2000/12/01 20:23:23  cdj
// now uses DynamicLoader package
//

// system include files

// user include files
#include "DynamicLoader/DLMultiFactoryChooserBase.h"

// forward declarations

class LoaderMultiFactoryChooser : public DLMultiFactoryChooserBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      LoaderMultiFactoryChooser() {}
      //virtual ~LoaderMultiFactoryChooser();

      // ---------- member functions ---------------------------
      
      virtual std::vector<std::string>::iterator 
           choose( const std::string& iShortName,
		   std::vector<std::string>::iterator itBegin,
		   std::vector<std::string>::iterator itEnd ) ;

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      LoaderMultiFactoryChooser( const LoaderMultiFactoryChooser& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const LoaderMultiFactoryChooser& operator=( const LoaderMultiFactoryChooser& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "CommandPattern/Template/LoaderMultiFactoryChooser.cc"
//#endif

#endif /* COMMANDPATTERN_LOADERMULTIFACTORYCHOOSER_H */
