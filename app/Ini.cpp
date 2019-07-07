#include "Ini.h"
#include "utils/INIreader.h"

namespace {
utils::INIreader &iniReader = utils::INIreader::instance();
}

utils::INIreader &IniReader()
{
   return iniReader;
}
