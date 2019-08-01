#ifndef SINGLETON_H
#define SINGLETON_H

namespace utils {

/// Base class for singletons. Based on Scott Meyers approach to guarantee
/// a thread safe instantiation.
template <typename T> class Singleton
{
public:
    /// Garantees thread safe instantiation.
   static T &instance()
   {
      static T instance;
      return instance;
   }
   Singleton<T>(const Singleton<T> &) = delete;
   Singleton<T> &operator=(const Singleton<T> &) = delete;
   Singleton<T>(const Singleton<T> &&) = delete;
   Singleton<T> &operator=(const Singleton<T> &&) = delete;
   virtual ~Singleton<T>() = default;

protected:
   Singleton<T>() = default;
};

} // namespace utils

#endif
