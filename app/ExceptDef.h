#ifndef EXCEPTDEF_H
#define EXCEPTDEF_H

#include <boost/filesystem.hpp>
#include <stdexcept>

#define STRINGIZE(s) STRINGIZE_(s)
#define STRINGIZE_(s) #s
#define __AT__                                                            \
   boost::filesystem::path(__FILE__).filename() +                         \
      ":" STRINGIZE(__LINE__) " "

#define THROW_RTE(msg) throw std::runtime_error(__AT__ #msg)

#endif
