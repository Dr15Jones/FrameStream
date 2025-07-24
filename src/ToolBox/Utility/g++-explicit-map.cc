#include <map>

int main()
{
   map< int , float , less< int > > a ;
   for ( map< int , float , less< int > >::const_iterator b( a.begin() ) ;
	 b != a.end() ;
	 ++b ) {
      float c( (*b).first*(*b).second ) ;
   }
   for ( map< int , float , less< int > >::iterator b( a.begin() ) ;
	 b != a.end() ;
	 ++b ) {
      float c( (*b).first*(*b).second ) ;
   }
}

template class map< int , float , less< int > > ;
template class std::pair< const int , float > ;

template bool operator!=( const rb_tree< int , std::pair< const int , float > , select1st<std::pair< const int , float > , int > , less< int > >::const_iterator&, const rb_tree< int , std::pair< const int , float > , select1st<std::pair< const int , float > , int > , less< int > >::const_iterator& ) ;
template bool operator!=( const rb_tree< int , std::pair< const int , float > , select1st<std::pair< const int , float > , int > , less< int > >::const_iterator&, const rb_tree< int , std::pair< const int , float > , select1st<std::pair< const int , float > , int > , less< int > >::iterator&) ;
template bool operator!=( const rb_tree< int , std::pair< const int , float > , select1st<std::pair< const int , float > , int > , less< int > >::iterator&, const rb_tree< int , std::pair< const int , float > , select1st<std::pair< const int , float > , int > , less< int > >::iterator&) ;

template class rb_tree< int , std::pair< const int , float > , select1st<std::pair< const int , float > , int > , less< int > > ;
template void construct( std::pair< const int , float >* , const std::pair< const int , float >& ) ;
template class select1st< std::pair< const int , float > , int > ;
template void swap( rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::rb_tree_node*& , rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::rb_tree_node*& ) ;
template void swap( rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::rb_tree_node*& , rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::rb_tree_node*& ) ;
template bool operator!=( const rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator& , const rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator& ) ;
template void deallocate( rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::rb_tree_node* ) ;
template void allocate( long , rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::rb_tree_node* ) ;
template class allocator< rb_tree< int , std::pair< const int , float >, select1st< std::pair< const int , float > , int > , less< int > >::rb_tree_node > ;

template class rb_tree_iterator< int , std::pair< const int , float >, select1st< std::pair< const int , float > , int > , less< int > > ;
template class std::pair< rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::iterator , bool > ;
template void distance( rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::iterator , rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::iterator , unsigned long & ) ;
template class reverse_bidirectional_iterator< rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::iterator , std::pair< const int , float > , std::pair< const int , float >& , long > ;
template bidirectional_iterator_tag iterator_category( rb_tree< int, std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::iterator ) ;
template void __distance( rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::iterator , rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::iterator , unsigned long &, bidirectional_iterator_tag ) ;
template class std::pair< rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::iterator , rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::iterator> ;

template class rb_tree_const_iterator< int , std::pair< const int , float >, select1st< std::pair< const int , float > , int > , less< int > > ;
template class std::pair< rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator , bool > ;
template void distance( rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator , rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator , unsigned long & ) ;
template class reverse_bidirectional_iterator< rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator , std::pair< const int , float > , const std::pair< const int , float >& , long > ;
template bidirectional_iterator_tag iterator_category( rb_tree< int, std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator ) ;
template void __distance( rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator , rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator , unsigned long &, bidirectional_iterator_tag ) ;
template class std::pair< rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator , rb_tree< int , std::pair< const int , float > , select1st< std::pair< const int , float > , int > , less< int > >::const_iterator> ;

template class rb_tree_pair_iterator_bool< int , std::pair< const int , float >, select1st< std::pair< const int , float > , int > , less< int > > ;

template class less< int > ;
template void swap( less< int >& , less< int >& ) ;
template void swap( __rb_color_type &, __rb_color_type & ) ;
template void swap(unsigned long &, unsigned long &) ;
template void swap(bool &, bool &) ;
template const unsigned long& max( const unsigned long& , const unsigned long& ) ;
