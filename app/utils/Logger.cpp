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
   m_logFile.close();
}

void utils::Logger::setFilename(const std::string &filename)
{
   SET_FNAME("Logger::setFilename()");
   m_logFile.close();
   m_logFile.open(filename.c_str());
   if (m_logFile) {
      m_filename = filename;
   }
   LOGI("LOGGER filename: " + m_filename.c_str());
}

void utils::Logger::log(const std::string &message)
{
   boost::mutex::scoped_lock lock(m_logMutex);
   m_logFile << boost::get_system_time() << "  " << message << std::endl;
}

void utils::Logger::log(const char *message)
{
   boost::mutex::scoped_lock lock(m_logMutex);
   m_logFile << boost::get_system_time() << "  " << message << std::endl;
}

utils::Logger::Logger()
   : m_logMutex()
   , m_filename()
   , m_logFile(APPNAME ".log")
   , m_debugMode(true)
{
}
