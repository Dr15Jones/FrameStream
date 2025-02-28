// -*- C++ -*-
#if !defined(PROCESSOR_PROCNAME_H)
#define PROCESSOR_PROCNAME_H
//
// Package:     Processor
// Module:      procname
//
/**\class procname procname.h procname/procname.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Martin Lohner
// Created:     Thu Dec 11 16:32:06 EST 1997
// $Id: FortranProc.h,v 1.4 2000/11/18 03:49:02 marsh Exp $
//
// Revision history
//
// $Log: FortranProc.h,v $
// Revision 1.4  2000/11/18 03:49:02  marsh
// Moved emacs mode hint to the top of the file, where emacs will actually
// look at it.
//
// Revision 1.3  1999/10/07 13:11:44  marsh
// Changed Description and Usage comment sections to doxygen format.
//
// Revision 1.2  1999/09/07 14:17:08  mkl
// switch to new Histogram Interface
//
// Revision 1.1  1998/02/10 03:41:38  mkl
// first version of FortranProcessor skeletons
//

// system include files

// user include files
#include "FortranProcessor/FortranProcessor.h"

// forward declarations
class procname : public FortranProcessor
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      procname( void );                      // anal1 
      virtual ~procname();                   // anal5 

      // member functions

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // implementation methods -- called by base class FortranProcessor
      virtual void implementInitialize( void );
      virtual void implementTerminate( void );
      virtual void implementHistBook( HIHistoManager& );

      virtual ActionBase::ActionResult implementEvent( Frame& iFrame );
      virtual ActionBase::ActionResult implementBeginRun( Frame& iFrame);
      virtual ActionBase::ActionResult implementEndRun( Frame& iFrame);
      //virtual ActionBase::ActionResult implementGeometry( Frame& iFrame);
      //virtual ActionBase::ActionResult implementHardware( Frame& iFrame);
      //virtual ActionBase::ActionResult implementUser( Frame& iFrame);

      // protected const member functions

   private:
      // Constructors and destructor
      procname( const procname& ); // stop default

      // assignment operator(s)
      const procname& operator=( const procname& ); // stop default

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* PROCESSOR_PROCNAME_H */
