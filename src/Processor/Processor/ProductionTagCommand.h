#if !defined(PROCESSOR_PRODUCTIONTAGCOMMAND_H)
#define PROCESSOR_PRODUCTIONTAGCOMMAND_H
// -*- C++ -*-
//
// Package:     <Processor>
// Module:      ProductionTagCommand
// 
/**\class ProductionTagCommand ProductionTagCommand.h Processor/ProductionTagCommand.h

 Description: Provides the 'production_tag' command for all Producers

 Usage:
    Follows the same implementation as ParameterBase.

*/
//
// Author:      Chris D Jones
// Created:     Fri Oct  8 22:47:02 EDT 1999
// $Id: ProductionTagCommand.h,v 1.1 1999/10/09 21:57:48 cdj Exp $
//
// Revision history
//
// $Log: ProductionTagCommand.h,v $
// Revision 1.1  1999/10/09 21:57:48  cdj
// added production_tag command to Producer
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class Producer;

class ProductionTagCommand : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ProductionTagCommand( const Name& iName, Producer* iTarget );
      virtual ~ProductionTagCommand();

      // ---------- member functions ---------------------------
      virtual int execute( int argc, char* argv[] ); // template method
      virtual int helpHandler();

      // ---------- const member functions ---------------------
      virtual int setHandler(); 
      virtual int setDefaultHandler(); 
      virtual int listHandler() ; 

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ProductionTagCommand( const ProductionTagCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ProductionTagCommand& operator=( const ProductionTagCommand& ); // stop default

      // ---------- private member functions -------------------
      Producer* producer();

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

#include "Processor/Producer.h"
// inline function definitions
inline
Producer* 
ProductionTagCommand::producer()  {
   //reinterpret_cast does not handle multiple inheritance
   // and we don't have dynamic_cast on all of our compilers
   // however, the old casting mechanism does the right thing
   return (Producer*)(target()); 
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Processor/Template/ProductionTagCommand.cc"
//#endif

#endif /* PROCESSOR_PRODUCTIONTAGCOMMAND_H */
