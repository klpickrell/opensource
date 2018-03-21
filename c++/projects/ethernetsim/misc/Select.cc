#include <sstream>
#include <sys/select.h>
#include <sys/time.h>
#include <cerrno>
#include <algorithm>
#include <cmath>
#include "Select.h"
#include "ErrnoException.h"

const SelectManager::When SelectManager::Readable;
const SelectManager::When SelectManager::Writeable;

SelectManager* SelectManager::instance()
{
   static SelectManager instance;
   return &instance;
}

SelectManager::SelectManager() : inSelect(0) { }

int SelectManager::count(When when) const
{
   int n = 0;
   for (Descriptors::const_iterator i = descriptors.begin();
         i != descriptors.end(); ++i)
      if (i->get<1>() & when)
         ++n;
   return n;
}

int SelectManager::count(int descriptor, When when) const
{
   int n = 0;
   for (Descriptors::const_iterator i = descriptors.begin();
         i != descriptors.end(); ++i)
      if (i->get<0>() == descriptor && i->get<1>() & when)
         ++n;
   return n;
}

void SelectManager::add(int descriptor, When when, const SelectSlot& slot)
{
   Updater updater;

   if (descriptor < 0)
   {
      std::ostringstream os;
      os << "SelectManager::add(): attempt to add invalid file descriptor "
         << "[" << descriptor << "]";
      throw std::runtime_error(os.str());
   }

   remove(descriptor, when);

   if (when & Readable)
      queuedDescriptors.push_back(
            boost::make_tuple(descriptor, Readable, slot));
   if (when & Writeable)
      queuedDescriptors.push_back(
            boost::make_tuple(descriptor, Writeable, slot));
}

void SelectManager::remove(int descriptor, When when)
{
   Updater updater;

   for (int i = 0; i < descriptors.size(); ++i)
      if (descriptors[i].get<0>() == descriptor &&
            descriptors[i].get<1>() & when)
         descriptors[i].get<1>() = 0;

   Descriptors::iterator i = queuedDescriptors.begin();
   while (i != queuedDescriptors.end())
      if (i->get<0>() == descriptor && i->get<1>() & when)
         i = queuedDescriptors.erase(i);
      else
         ++i;
}

void SelectManager::select(bool poll, double tsec) const
{
   if (inSelect)
      throw std::runtime_error("SelectManager::select() called reentrantly");

   if (descriptors.empty())
      return;

   Updater updater(true);

   fd_set readset;
   fd_set writeset;

   FD_ZERO(&readset);
   FD_ZERO(&writeset);

   int maxSocket = -1;
   for (int i = 0; i < descriptors.size(); ++i)
   {
      int descriptor = descriptors[i].get<0>();
      When when = descriptors[i].get<1>();

      if (when & Readable)
         FD_SET(descriptor, &readset);
      if (when & Writeable)
         FD_SET(descriptor, &writeset);

      maxSocket = std::max(maxSocket, descriptor);
   }

   int status;
   if (poll)
   {
       double intpart;
       struct timeval t;

       t.tv_sec = (int)tsec;
       t.tv_usec = (int)(modf( tsec, &intpart ) * 1e6);

       status = ::select(maxSocket + 1, &readset, &writeset, 0, &t);
   }
   else
      status = ::select(maxSocket + 1, &readset, &writeset, 0, 0);

   if (status == 0)
      return;

   if (status == -1)
      if (errno == EINTR)
         return;
      else
         throw ErrnoException(errno, "select");

   for (int i = 0; i < descriptors.size(); ++i)
   {
      const int& descriptor = descriptors[i].get<0>();
      const volatile When& when = descriptors[i].get<1>();
      const SelectSlot& slot = descriptors[i].get<2>();

      if (when & Readable && FD_ISSET(descriptor, &readset))
         slot(descriptor);
      
      if (when & Writeable && FD_ISSET(descriptor, &writeset))
         slot(descriptor);
   }
}

void SelectManager::update()
{
   if (inSelect)
      return;

   Descriptors::iterator i = descriptors.begin();
   while (i != descriptors.end())
      if (i->get<1>() == 0)
         i = descriptors.erase(i);
      else
         ++i;

   descriptors.insert(descriptors.end(),
         queuedDescriptors.begin(), 
         queuedDescriptors.end());
   queuedDescriptors.clear();
}

SelectManager::Updater::Updater(bool fromSelect) : fromSelect(fromSelect)
{
   if (fromSelect)
      ++SelectManager::instance()->inSelect;
}

SelectManager::Updater::~Updater()
{
   if (fromSelect)
      --SelectManager::instance()->inSelect;
   SelectManager::instance()->update();
}
