#ifndef SelectManager_h
#define SelectManager_h

#include <vector>
#include <boost/function.hpp>
#include <boost/tuple/tuple.hpp>

class SelectManager  // Singleton
{
public:
   typedef int When;
   static const When Readable = 4;
   static const When Writeable = 2;

   typedef boost::function<void (int descriptor)> Function;
   typedef Function SelectSlot;

   static SelectManager* instance();

   void add(int descriptor, When when, const SelectSlot& slot);
   void remove(int descriptor, When when = Readable | Writeable);

   int count() const { return descriptors.size(); }
   int count(When when) const;
   int count(int descriptor, When when) const;

   void select(bool poll = false, double tsec=0) const;

private:
   class Updater
   {
   public:
      Updater(bool fromSelect = false);
      ~Updater();
   private:
      bool fromSelect;
   };

   SelectManager();
   void update();

   typedef std::vector< boost::tuple< int, When, Function > > Descriptors;
   Descriptors descriptors;
   Descriptors queuedDescriptors;
   int inSelect;

   friend class Updater;
};

#endif  // !SelectManager_h
