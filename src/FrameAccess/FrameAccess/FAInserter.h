#if !defined(FRAMEACCESS_FAINSERTER_H)
#define FRAMEACCESS_FAINSERTER_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FAInserter
// 
/**\class FAInserter FAInserter.h FrameAccess/FAInserter.h

 Description: Allows easy insertion of data into the Frame

 Usage:
    Use this class in a Processor when you want to be able to insert
    data into the Frame from one of your bound functions.

    In the Processor's class decleration, add
    \code
      //data to be inserted into the Frame
      FAInserter< MyData > m_myDataInserter;
    \endcode
    Then in the Processor's constructor, register a ProxyFactory that
     will create a Proxy that will return the value inserted into the 
     FAInserter

     \code
      //make MyData available in the Event record
      registerProxyFactory( Stream::kEvent, 
                            m_myDataInserter.makeFactory(),
			    UsageTag() );
     \endcode

   Finally, in your bound function, insert your data into the FAInserter
   
   \code
      MyProc::event( Frame& iFrame ) 
      {
        ...
        // create some new data we want inserted
        MyData* myData = new MyData(...);
        ...
        //insert the data into the Frame
        m_myDataInserter.insert( myData );
	...
      }
  \endcode

  Memory management
    If you pass 'true' or nothing at all to the FAInserter's constructor,
     then the FAInserter will manage the memory.  This means that everytime
     a new Record appears in the Stream that you put the ProxyFactory, 
     FAInserter will delete the value you 'insert'ed and set its internal
     value to 0.
    If you pass 'false' to the FAInserter's constructor, then you will
     be responsible for managing the memory to the object you insert into
     the FAInserter.
*/
//
// Author:      Chris D Jones
// Created:     Sat Oct 30 19:42:50 EDT 1999
// $Id: FAInserter.h,v 1.4 2001/04/17 01:08:35 cleo3 Exp $
//
// Revision history
//
// $Log: FAInserter.h,v $
// Revision 1.4  2001/04/17 01:08:35  cleo3
// modified to compile under linux
//
// Revision 1.3  2000/03/19 14:53:49  cdj
// FAInserter now uses a Proxy that inherits from DataSourceProxy
//
// Revision 1.2  1999/10/31 15:03:50  cdj
// fixed doxygenated comments
//
// Revision 1.1  1999/10/31 01:03:53  cdj
// added FAInserter
//

// system include files

// user include files
#include "DataDelivery/DataSourceProxy.h"
#include "DataHandler/ProxyFactoryBase.h"
#include "DataHandler/RecordMethods.h"

// forward declarations

template< class T >
class FAInserter
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------

      /// set true if you want Inserter to handle deletion of data
      FAInserter( DABoolean iOwnsMemory = true ) :
	 m_ownsMemory(iOwnsMemory), m_value(0){}
      ~FAInserter() { deleteValue(); }

      // ---------- member functions ---------------------------
      /** call this function in the body of your Processor's bound function. 
	Takes ownership of the value if constructor was passed 'true'
       */
      void insert( T* iValue ) { deleteValue(); m_value = iValue; }

      void deleteValue() { 
	 if(m_ownsMemory) { delete m_value; } 
	 m_value=0; }
      
      //define the factory class here, since this is the only place
      // it well ever be used
      class FAIProxyFactory : public ProxyFactoryBase {
	 public:
	    FAIProxyFactory( FAInserter<T>* iInserter ) :
	       m_inserter( iInserter) {}
	    
	    //define Proxy here, since this is the only place
	    //it will be used
	    class FAIProxy : public DataSourceProxy<T> {
	       public:
		  FAIProxy( FAInserter<T>* iInserter ) 
		     : m_inserter( iInserter ) {}
		  protected:
		  void invalidateCache() {
		     m_inserter->deleteValue();
		  }
		  
		  const T* faultHandler( const Record&,
					 const DataKey& ) {
		     return m_inserter->value();
		  }
	       private:
		  FAInserter<T>* m_inserter;
	    };
	    
	    virtual ProxyBase* makeProxy() const {
	       
	       return new FAIProxy( m_inserter );
	    }
	    
	    DataKey makeKey( const UsageTag& iUsage,
			     const ProductionTag& iProduction ) const {
	       return RecordMethods<T>::makeKey( iUsage, iProduction );
	    }
	 private:
	    FAInserter<T>* m_inserter;
      };
      
      /// call this within the Processor's registerProxyFactory function
      ProxyFactoryBase* makeFactory() {
	 return new FAIProxyFactory( this ); 
      }

      // ---------- const member functions ---------------------
      /** returns the value passed in the insert() method or
	  0 if deleteValue() was called
       */
      T* value() const { return m_value; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FAInserter( const FAInserter& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FAInserter& operator=( const FAInserter& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- value members -------------------------------
      DABoolean m_ownsMemory;
      T* m_value;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "FrameAccess/Template/FAInserter.cc"
//#endif

#endif /* FRAMEACCESS_FAINSERTER_H */
