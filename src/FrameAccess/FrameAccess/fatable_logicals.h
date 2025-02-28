#if !defined(FRAMEACCESS_FATABLE_LOGICALS_H)
#define FRAMEACCESS_FATABLE_LOGICALS_H
// -*- C++ -*-
//
// Package:     <FrameAccess>
// Module:      fatable_logicals
// 
/**\class fatable_logicals fatable_logicals.h FrameAccess/fatable_logicals.h

 Description: Do 'set' operations on FATables

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Thu Feb 12 13:35:41 EST 2004
// $Id: fatable_logicals.h,v 1.1 2004/02/13 20:41:36 cdj Exp $
//
// Revision history
//
// $Log: fatable_logicals.h,v $
// Revision 1.1  2004/02/13 20:41:36  cdj
// first submission
//

// system include files

// user include files
#include "FrameAccess/FATable.h"

// forward declarations
namespace FALogicals {
   template <class T>
      class TableHolder {
	 public:
	    typedef T value_type;
	    typedef typename T::Identifier Identifier;

	    TableHolder(FATable<T> iTable ) : 
	       m_table(iTable),
	       m_present(iTable.begin()),
	       m_atEnd( iTable.size() == 0 ) {}
	    void sumAtEnd(unsigned long& oNEnd) const {
	       if( m_atEnd) { ++oNEnd; } }
	    void sumLists(unsigned long& oNLists) const {
	       ++oNLists;
	    }
	    FAItem<T> front() const {
	       return (m_table.begin());
	    }
	    FAItem<T> back() const {
	       return ( m_table.size() ? (m_table.end()-1) : (m_table.end()));
	    }

	    DABoolean pass(const Identifier& iID, Identifier& ioNextID,
			   unsigned long &oNEnd, const T*& oItem) const {
	       if(m_atEnd) {
		  return false;
	       }
	       if( m_present->identifier() != iID) {
		  if(m_present->identifier() < ioNextID) {
		     ioNextID = m_present->identifier();
		  }
		  return false;
	       }
	       oItem = &(*m_present);
	       ++m_present;
	       if(m_present == m_table.end()) {
		  ++oNEnd;
		  m_atEnd = true;
	       } else {
		  if(m_present->identifier() < ioNextID) {
		     ioNextID = m_present->identifier();
		  }
	       }
	       return true;
	    }
	 private:
	    FATable<T> m_table;
	    mutable typename FATable<T>::const_iterator m_present;
	    mutable DABoolean m_atEnd;
      };

   template< class TL, class TR>
      class BinaryOp {
	 public:
	    typedef typename TL::value_type value_type;
	    typedef typename TL::Identifier Identifier;

	    BinaryOp( const TL& iLeft, const TR& iRight) :
	       m_left(iLeft), m_right(iRight) {}
	    TL& left() { return m_left;}
	    TR& right() { return m_right;}

	    const TL& left() const { return m_left;}
	    const TR& right() const { return m_right;}


	    void sumAtEnd(unsigned long& oNEnd) const {
	       m_left.sumAtEnd(oNEnd);
	       m_right.sumAtEnd(oNEnd);
	    }

	    void sumLists(unsigned long& oNLists) const {
	       m_left.sumLists(oNLists);
	       m_right.sumLists(oNLists);
	    }

	    FAItem<value_type> front() const {
	       FAItem<value_type> m_leftFront = m_left.front();
	       FAItem<value_type> m_rightFront = m_right.front();

	       if( m_leftFront.valid() ) {
		  if(m_rightFront.valid() ) {
		     if(m_leftFront->identifier() >
			m_rightFront->identifier() ) {
			return m_rightFront;
		     } else {
			return m_leftFront;
		     }
		  } else {
		     return m_leftFront;
		  }
	       }
	       return m_rightFront;
	    }

	    FAItem<value_type> back() const {
	       FAItem<value_type> m_leftBack = m_left.back();
	       FAItem<value_type> m_rightBack = m_right.back();

	       if( m_leftBack.valid() ) {
		  if(m_rightBack.valid() ) {
		     if(m_leftBack->identifier() <
			m_rightBack->identifier() ) {
			return m_rightBack;
		     } else {
			return m_leftBack;
		     }
		  } else {
		     return m_leftBack;
		  }
	       }
	       return m_rightBack;
	    }
	 protected:
	    template <class TImp>
	    static void fillImp(const TImp& iImp,
				FAConstPtrTable<value_type>& iToFill){
	       unsigned long nEnd = 0;
	       iImp.sumAtEnd(nEnd);
	       unsigned long nLists = 0;
	       iImp.sumLists(nLists);
	       
	       if(nEnd == nLists) {
		  return;
	       }
	       Identifier nID = iImp.front()->identifier();
	       const Identifier lastID = iImp.back()->identifier();
	       const value_type* item;
	       while( nEnd != nLists ) {
		  Identifier nNextID = lastID;
		  if( iImp.pass( nID, nNextID, nEnd, item) ) {
		     iToFill.insert( const_cast<value_type*>(item) );
		  }
		  nID = nNextID;
	       }
	    }
	 private:
	    TL m_left;
	    TR m_right;
      };

   template<class TL, class TR>
      class AndOp : public BinaryOp<TL, TR> {
	 public:
	    typedef typename BinaryOp<TL, TR>::Identifier Identifier;
	    typedef typename BinaryOp<TL, TR>::value_type value_type;

	    AndOp(const TL& iLeft, const TR& iRight) : BinaryOp<TL,TR>(iLeft, iRight) {}
	    
	    DABoolean pass(const Identifier& iID, Identifier& ioNextID,
			   unsigned long &oNEnd, const value_type*& oItem) const {
	       DABoolean leftAnswer = left().pass(iID, ioNextID,
						  oNEnd, oItem);
	       DABoolean rightAnswer = right().pass(iID, ioNextID,
						    oNEnd, oItem);
	       return leftAnswer&&rightAnswer;
	    }
	    void fill(FAConstPtrTable<value_type>& iToFill) const {
	       fillImp(*this, iToFill);
	    }
      };

   template<class TL, class TR>
      class OrOp : public BinaryOp<TL, TR> {
	 public:
	    typedef typename BinaryOp<TL, TR>::Identifier Identifier;
	    typedef typename BinaryOp<TL, TR>::value_type value_type;
	    
	    OrOp(const TL& iLeft, const TR& iRight) : BinaryOp<TL,TR>(iLeft, iRight) {}
	    
	    DABoolean pass(const Identifier& iID, Identifier& ioNextID,
			   unsigned long &oNEnd, const value_type*& oItem) const {
	       DABoolean leftAnswer = left().pass(iID, ioNextID,
						  oNEnd, oItem);
	       DABoolean rightAnswer = right().pass(iID, ioNextID,
						    oNEnd, oItem);
	       return leftAnswer||rightAnswer;
	    }
	    void fill(FAConstPtrTable<value_type>& iToFill) const {
	       fillImp(*this, iToFill);
	    }
      };


   template <class T>
      class NotOp {
	    typedef typename T::value_type value_type;
	    typedef typename T::Identifier Identifier;
	 public:
	    NotOp(const T& iItem ) : 
	       m_item(iItem) {}

	    void sumAtEnd(unsigned long& oNEnd) const {
	       m_item.sumAtEnd(oNEnd) ; }

	    void sumLists(unsigned long& oNLists) const {
	       m_item.sumLists(oNLists);
	    }
	    FAItem<value_type> front() const { return m_item.front(); }
	    FAItem<value_type> back() const { return m_item.back(); }


	    DABoolean pass(const Identifier& iID, Identifier& ioNextID,
			   unsigned long &oNEnd, const value_type*& oItem) const {
	       return !( m_item.pass(iID, ioNextID, oNEnd, oItem) );
	    }
	 private:
	    T m_item;
      };

#if !defined(SUNCC)
#define FA_CONST const
#else
#define FA_CONST
#endif

   template<class TL, class TR>
      inline
      AndOp<TL, TR> operator&&(FA_CONST TL& iLeft,FA_CONST TR& iRight) {
      return AndOp<TL, TR>( iLeft, iRight);
   }

   template<class TL, class TR>
      inline
      OrOp<TL, TR> operator||(FA_CONST TL& iLeft, FA_CONST TR& iRight) {
      return OrOp<TL, TR>( iLeft, iRight);
   }
   template<class T>
      inline
      NotOp<T> operator!(const T& iItem) {
      return NotOp<T>(iItem);
   }
}

template<class TItem>
inline
FALogicals::AndOp<FALogicals::TableHolder<TItem>, FALogicals::TableHolder<TItem> >
operator&&(FATable<TItem> iLeft, FATable<TItem> iRight) {
   typedef FALogicals::TableHolder<TItem> Holder;
   return FALogicals::AndOp<Holder,Holder > (
      Holder(iLeft), Holder(iRight) );
}

template<class T, class TItem>
inline
FALogicals::AndOp<T, FALogicals::TableHolder<TItem> >
operator&&( FA_CONST T& iLeft, FATable<TItem> iTable) {
   return FALogicals::AndOp<T, FALogicals::TableHolder<TItem> > (
      iLeft, iTable );
}

template<class T, class TItem>
inline
FALogicals::AndOp<FALogicals::TableHolder<TItem>,T >
operator&&(FATable<TItem> iTable, FA_CONST T& iRight) {
   return FALogicals::AndOp<FALogicals::TableHolder<TItem>,T > (
      iTable, iRight );
}

template<class TItem>
inline
FALogicals::OrOp<FALogicals::TableHolder<TItem>, FALogicals::TableHolder<TItem> >
operator||(FATable<TItem> iLeft, FATable<TItem> iRight) {
   typedef FALogicals::TableHolder<TItem> Holder;
   return FALogicals::OrOp<Holder,Holder > (
      Holder(iLeft), Holder(iRight) );
}

template<class T, class TItem>
inline
FALogicals::OrOp<T, FALogicals::TableHolder<TItem> >
operator||( FA_CONST T& iLeft, FATable<TItem> iTable) {
   return FALogicals::OrOp<T, FALogicals::TableHolder<TItem> > (
      iLeft, iTable );
}

template<class T, class TItem>
inline
FALogicals::OrOp<FALogicals::TableHolder<TItem>,T >
operator||(FA_CONST FATable<TItem>& iTable, FA_CONST T& iRight) {
   return FALogicals::OrOp<FALogicals::TableHolder<TItem>,T > (
      iTable, iRight );
}

template<class T>
inline
FALogicals::NotOp<FALogicals::TableHolder<T> >
operator!(FATable<T> iTable ) {
   return FALogicals::NotOp<FALogicals::TableHolder<T> >( iTable);
}

#endif /* FRAMEACCESS_FATABLE_LOGICALS_H */
