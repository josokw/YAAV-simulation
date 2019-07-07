#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <boost/thread/mutex.hpp>
#include <fstream>
#include <string>

namespace utils {

/// Logs messages to a file.
/// Implemented according to the singleton pattern.
class Logger
{
public:
   static Logger &instance();
   Logger(const Logger &) = delete;
   Logger &operator=(const Logger &) = delete;
   virtual ~Logger();

   void setFilename(const std::string &filename);
   void setDebugMode(bool on) { m_debugMode = on; }
   void log(const std::string &message);
   void log(const char *message);
   void logDebug(const std::string &message)
   {
      if (m_debugMode)
         log(message);
   }
   void logDebug(const char *message)
   {
      if (m_debugMode)
         log(message);
   }

protected:
   Logger();

private:
   boost::mutex m_logMutex;
   std::string m_filename;
   std::ofstream m_logFile;
   bool m_debugMode;
};

} // namespace utils

#endif // UTILS_LOGGER_H
