template <class T> class Bar;
template <class T>
Bar<T> foo( Bar<T>& );

template <class T> class Bar2;
template <class T>
Bar<T> foo( Bar2<T>& );

template <class T>
class Bar
{
#if !defined(TEMPLATE_FRIEND_OVERLOADED_FUNC_INSTANTIATE_BUG)
      friend Bar<T> foo<T>(Bar<T>&);
#else
   public:
#endif
      void doThis() { m_dummy = 1; }

#if defined(TEMPLATE_FRIEND_OVERLOADED_FUNC_INSTANTIATE_BUG)
   private:
#endif
      int m_dummy;
};

template <class T>
inline
Bar<T>
foo(  Bar<T>& iBar )
{
   iBar.doThis();
   return iBar;
}

int main()
{
   Bar<int> bar;

   foo( bar );

   return 0;
}


