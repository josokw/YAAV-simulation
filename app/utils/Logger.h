#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include "Singleton.h"

#include <fstream>
#include <mutex>
#include <string>

namespace utils {

/// Singleton class, logs messages to a file.
class Logger: public Singleton<Logger>
{
   friend class utils::Singleton<Logger>;

public:
   virtual ~Logger();

   void setFilename(const std::string &filename);
   void setDebugMode(bool on) { debugMode_ = on; }
   void log(const std::string &message);
   void log(const char *message);
   void logDebug(const std::string &message)
   {
      if (debugMode_)
         log(message);
   }
   void logDebug(const char *message)
   {
      if (debugMode_)
         log(message);
   }
   void logInfo(const std::string &message)
   {
      if (not debugMode_)
         log(message);
   }
   void logInfo(const char *message)
   {
      if (not debugMode_)
         log(message);
   }

protected:
   Logger();

private:
   std::mutex logMutex_;
   std::string filename_;
   std::ofstream logFile_;
   bool debugMode_;
};

} // namespace utils

#endif // UTILS_LOGGER_H
