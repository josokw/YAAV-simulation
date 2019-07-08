#include "stringExt.h"

#include <algorithm>

void utils::removeLeadingSpacesTabs(std::string &line)
{
   if (!line.empty()) {
      while (line[0] == ' ' or line[0] == '\t') {
         line.erase(0, 1);
      }
   }
}

void utils::removeTrailingSpacesTabs(std::string &line)
{
   if (!line.empty()) {
      while (line[line.size() - 1] == ' ' || line[line.size() - 1] == '\t') {
         line.erase(line.size() - 1, 1);
      }
   }
}

void utils::removeLeadingTrailingSpacesTabs(std::string &line)
{
   removeLeadingSpacesTabs(line);
   removeTrailingSpacesTabs(line);
}

void utils::replaceCommasBySpaces(std::string &line)
{
   size_t pos;
   while ((pos = line.find(std::string(","))) != std::string::npos) {
      line.replace(pos, 1, " ");
   }
}

void utils::removeReturns(std::string &line)
{
   line.erase(std::remove(begin(line), end(line), '\n'), end(line));
}

void utils::tokenize(const std::string &str, std::vector<std::string> &tokens,
                     const std::string &delimiters)
{
   // Skip delimiters at beginning.
   std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
   // Find first "non-delimiter".
   std::string::size_type pos = str.find_first_of(delimiters, lastPos);

   while (std::string::npos != pos || std::string::npos != lastPos) {
      // Found a token, add it to the vector.
      tokens.push_back(str.substr(lastPos, pos - lastPos));
      // Skip delimiters. Note the "not_of"
      lastPos = str.find_first_not_of(delimiters, pos);
      // Find next "non-delimiter"
      pos = str.find_first_of(delimiters, lastPos);
   }
}

void utils::decapitalize(std::string &input)
{
   for (auto &c : input) {
      c = tolower(c);
   }
}

void utils::capitalize(std::string &input)
{
   for (auto &c : input) {
      c = toupper(c);
   }
}
