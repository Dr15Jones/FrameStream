#include "Experiment/Experiment.h"
#include "FrameAccess/FAPtrTable.h"

class Dummy
{
   public:
      Dummy(int a):m_id(a){}
      typedef int Identifier;
      int identifier() const { return m_id; }
   private:
      int m_id;
};

int main()
{

   FAPtrTable<Dummy> table;
   //test different types of inserts:
   //multiple insertions, indexable insertions, non-indexable insertions,
   //insertions at the beginning, end, middle.
   table.insert(new Dummy(1));
   table.insert(new Dummy(2));
   table.insert(new Dummy(3));
   table.insert(new Dummy(4));
   table.insert(new Dummy(7));
   table.insert(new Dummy(7));
   table.insert(new Dummy(3));
   table.insert(new Dummy(6));
   table.insert(new Dummy(0));
   table.insert(new Dummy(0));
   table.insert(new Dummy(4));
   table.insert(new Dummy(5));
   table.insert(new Dummy(4));
   table.insert(new Dummy(4));
   table.insert(new Dummy(9));
   table.insert(new Dummy(10));
   table.insert(new Dummy(4));

   //print it out, make sure we have a sorted, unique table
   FAPtrTable<Dummy>::const_iterator itrEnd = table.end();
   for(FAPtrTable<Dummy>::const_iterator itr = table.begin(); itr != itrEnd;
       ++itr)
   {
      cout<< (*itr).identifier() << std::endl;
   }
   
   return 0;
}

typedef Dummy _many_element_;
#include "FrameAccess/instantiate_FATable.h"
typedef int _favoidptrcontainer_integral_type_;
#include "FrameAccess/instantiate_FAVoidPtrContainer_integral_type.h"
