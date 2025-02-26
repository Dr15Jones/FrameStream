#include <set>

int main()
{
   set< int , less< int > > a ;
   for ( set< int , less< int > >::const_iterator b( a.begin() ) ;
	 b != a.end() ;
	 ++b ) {
      float c( (*b) ) ;
   }
   for ( set< int , less< int > >::iterator b( a.begin() ) ;
	 b != a.end() ;
	 ++b ) {
      float c( (*b) ) ;
   }
}

template class set< int , less< int > > ;

template void operator!=( const rb_tree< int , int , ident< int , int > , less< int > >::const_iterator& , const rb_tree< int , int , ident< int , int > , less< int > >::const_iterator& ) ;
template void operator!=( const rb_tree< int , int , ident< int , int > , less< int > >::const_iterator& , const rb_tree< int , int , ident< int , int > , less< int > >::iterator& ) ;
template void operator!=( const rb_tree< int , int , ident< int , int > , less< int > >::iterator& , const rb_tree< int , int , ident< int , int > , less< int > >::iterator& ) ;

template class rb_tree< int , int , ident< int , int > , less< int > > ;
template void construct(int* , const int &) ;
template class ident< int , int > ;
template void swap( rb_tree< int , int , ident< int , int > , less< int > >::rb_tree_node*& , rb_tree< int , int , ident< int , int > , less< int > >::rb_tree_node*& ) ;
template void deallocate( rb_tree< int , int , ident< int , int > , less< int > >::rb_tree_node* ) ;
template void allocate( long , rb_tree< int , int , ident< int , int > , less< int > >::rb_tree_node* ) ;
template class allocator< rb_tree< int , int , ident< int , int > , less< int > >::rb_tree_node > ;

template class rb_tree_const_iterator< int , int , ident< int , int > , less< int > > ;
template void distance( rb_tree< int , int , ident< int , int > , less< int > >::const_iterator , rb_tree< int , int , ident< int , int > , less< int > >::const_iterator , unsigned long& ) ;
template class pair< rb_tree< int , int , ident< int , int > , less< int > >::const_iterator , bool > ;
template class pair< rb_tree< int , int , ident< int , int > , less< int > >::const_iterator , rb_tree< int , int , ident< int , int > , less< int > > > ;
template class pair< rb_tree< int , int , ident< int , int > , less< int > >::const_iterator , rb_tree< int , int , ident< int , int > , less< int > >::const_iterator > ;
template class reverse_bidirectional_iterator< rb_tree< int , int , ident< int , int > , less< int > >::const_iterator , int , const int& , long > ;
template bidirectional_iterator_tag iterator_category( rb_tree< int , int , ident< int , int > , less< int > >::const_iterator ) ;
template void __distance( rb_tree< int , int , ident< int , int > , less< int > >::const_iterator , rb_tree< int , int , ident< int , int > , less< int > >::const_iterator , unsigned long& , bidirectional_iterator_tag ) ;

template class rb_tree_iterator< int , int , ident< int , int > , less< int > > ;
template void distance( rb_tree< int , int , ident< int , int > , less< int > >::iterator , rb_tree< int , int , ident< int , int > , less< int > >::iterator , unsigned long& ) ;
template class pair< rb_tree< int , int , ident< int , int > , less< int > >::iterator , bool > ;
template class pair< rb_tree< int , int , ident< int , int > , less< int > >::iterator , rb_tree< int , int , ident< int , int > , less< int > > > ;
template class pair< rb_tree< int , int , ident< int , int > , less< int > >::iterator , rb_tree< int , int , ident< int , int > , less< int > >::iterator > ;
template class reverse_bidirectional_iterator< rb_tree< int , int , ident< int , int > , less< int > >::iterator , int , int& , long > ;
template bidirectional_iterator_tag iterator_category( rb_tree< int , int , ident< int , int > , less< int > >::iterator ) ;
template void __distance( rb_tree< int , int , ident< int , int > , less< int > >::iterator , rb_tree< int , int , ident< int , int > , less< int > >::iterator , unsigned long& , bidirectional_iterator_tag ) ;

template class rb_tree_pair_iterator_bool< int , int , ident< int , int > , less< int > > ;

template class less< int > ;
template void swap( less< int >& , less< int >& ) ;
template void swap( __rb_color_type &, __rb_color_type & ) ;
template void swap(unsigned long &, unsigned long &) ;
template void swap(bool &, bool &) ;
 template const unsigned long& max( const unsigned long& , const unsigned long& ) ;
