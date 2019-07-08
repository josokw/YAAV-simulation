#include "Logger.h"
#include "AppInfo.h"
#include "Log.h"

#include <boost/date_time.hpp>
#include <boost/thread.hpp>

utils::Logger &utils::Logger::instance()
{
   static Logger logger;
   return logger;
}

utils::Logger::~Logger()
{
   SET_FNAME("Logger::~Logger()");
   LOGI("LOGGER closed");
   logFile_.close();
}

void utils::Logger::setFilename(const std::string &filename)
{
   std::lock_guard<std::mutex> lock(logMutex_);
   SET_FNAME("Logger::setFilename()");
   logFile_.close();
   logFile_.open(filename.c_str());
   if (logFile_) {
      filename_ = filename;
   }
   LOGI("LOGGER filename: " + filename_);
}

void utils::Logger::log(const std::string &message)
{
   std::lock_guard<std::mutex> lock(logMutex_);
   logFile_ << boost::get_system_time() << "  " << message << std::endl;
}

void utils::Logger::log(const char *message)
{
   std::lock_guard<std::mutex> lock(logMutex_);
   logFile_ << boost::get_system_time() << "  " << message << std::endl;
}

utils::Logger::Logger()
   : logMutex_{}
   , filename_{}
   , logFile_{APPNAME ".log"}
   , debugMode_{true}
{
}
