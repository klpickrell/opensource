#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

// singleton: A singleton base class for implementing singleton objects
// Author: klpickrell
// Date: 2005-08-04

/**********************************************************************

This class provides some methods/members to implement the singleton
pattern.  It uses a static const auto_ptr that is initialized with
an instance of the derived class.  This means that it is created before
the main function gets called and deleted after main ends.  In this
case, there is no need for a destroy type function to be called at the
end of the program.  The downside is that the object is created regardless
of whether instance() is called.  Also, like most singleton implementations
you can only create a default constructor.  It is also incumbent upon the
developer to make this constructor private, otherwise you really don't have
a singleton.

example:

class onlyone : public singleton< onlyone >
{
     DECLARE_SINGLETON_FRIENDS( onlyone );

private:
     onlyone();
    ~onlyone();

public:

     int getmyvalue() { return myvalue; }
     void setmyvalue( int r ) { myvalue = r; }

private:

     int myvalue;
};

int main( int argc, char** argv )
{
    onlyone::instance()->setmyvalue( 5 );
    int val = onlyone::instance()->getmyvalue();

    return 0;
}

**********************************************************************/


#define DECLARE_SINGLETON_FRIENDS( X ) \
              friend class singleton< X >; \
              friend class std::auto_ptr< X >;

template< typename T > class singleton 
{
protected:

    static const std::auto_ptr< T > _instance;

    singleton();
    virtual ~singleton();

public:
    static T* instance() 
    {
        return _instance.get();
    }
};

template< typename T > const std::auto_ptr<T> singleton<T>::_instance( new T );

template< typename T > singleton< T >::singleton()
{
}
  
template< typename T > singleton< T >::~singleton()
{
}

#endif
