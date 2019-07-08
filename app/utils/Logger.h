#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <fstream>
#include <mutex>
#include <string>
#include <thread>

namespace utils {

/// Logs messages to a file.
/// Implemented according to the singleton pattern.
class Logger
{
public:
   static Logger &instance();

   Logger(const Logger &other) = delete;
   Logger &operator=(const Logger &other) = delete;
   Logger(const Logger &&other) = delete;
   Logger &operator=(const Logger &&other) = delete;
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
