#include <iostream>
#include <typeinfo>
#include <vector>
#include <boost/any.hpp>

using namespace std;

class Pipe
{
public:

   virtual ~Pipe() { }

   template <class T>
   void push(const T& v)
   {
      _push(boost::any(&v), boost::any(&v + 1));
   }
   template <class T>
   void push(const std::vector<T>& v)
   {
      _push(boost::any(&v[0]), boost::any(&v[0] + v.size()));
   }
   template <class T>
   void push(const T* first, const T* last)
   {
      if (first != last)
         _push(boost::any(first), boost::any(last));
   }

   bool compatible(const Pipe* pipe) const
   {
      return getType() && pipe->getType() ?
         (*getType() == *pipe->getType()) : true;
   }

   const std::type_info* getType() const { return type; }

   void setFilter(Filter* filter) { this->filter = filter; }
   Filter* getFilter() const { return filter; }

   virtual void sync();

protected:
   void applyFilter(const boost::any& first, const boost::any& last,
         bool flushing = false);

   virtual void doAboutToApplyFilter(const boost::any& /* first */,
         const boost::any& /* last */, bool /* flushing */) { }
   virtual void doAfterFilterApplied() { }

private:
   virtual void _push(const boost::any& first, const boost::any& last)
   {
      applyFilter(first, last);
   }

   const std::type_info* type;
   Filter* filter;

   friend class ProxyPipe;
};

template <class T>
class PipeT : public Pipe
{
public:
   PipeT(Filter* filter = 0) : Pipe(&typeid(T), filter) { }

   void push(const T& v)
   {
      Pipe::push(v);
   }
   void push(const std::vector<T>& v)
   {
      Pipe::push(v);
   }
   virtual void push(const T* first, const T* last)
   {
      applyFilter(first, last);
   }

protected:
   virtual void doAboutToApplyFilter(const T* /* first */,
         const T* /* last */, bool /* flushing */) { }

   void applyFilter(const T* first, const T* last, bool flushing = false)
   {
      Pipe::applyFilter(boost::any(first), boost::any(last), flushing);
   }

   virtual void doAboutToApplyFilter(const boost::any& first,
         const boost::any& last, bool flushing)
   {
      doAboutToApplyFilter(boost::any_cast<const T*>(first),
            boost::any_cast<const T*>(last), flushing);
   }

private:
   virtual void _push(const boost::any& first, const boost::any& last)
   {
      push(boost::any_cast<const T*>(first), boost::any_cast<const T*>(last));
   }
};



int main( int argc, char** argv )
{

    return 0;
}


