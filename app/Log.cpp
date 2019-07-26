#include "Log.h"
#include "utils/Logger.h"

namespace {
utils::Logger &logger = utils::Logger::instance();
}

void log(const std::string &msg)
{
   logger.log(msg);
}

void logDebug(const char *msg)
{
   logger.logDebug(msg);
}

void logDebug(const std::string &msg)
{
   logger.logDebug(msg);
}

void logInfo(const char *msg)
{
   logger.logInfo(msg);
}

void logInfo(const std::string &msg)
{
   logger.logInfo(msg);
}

void log(const char *msg)
{
   logger.log(msg);
}

void log(bool condition, const std::string &msg)
{
   if (condition)
      log(msg);
}

void log(bool condition, const char *msg)
{
   if (condition)
      log(msg);
}
