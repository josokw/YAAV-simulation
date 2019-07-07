#include "stringExt.h"

using namespace std;

void utils::removeLeadingSpacesTabs(string &line)
{
   if (!line.empty()) {
      while (line[0] == ' ' || line[0] == '\t') {
         line.erase(0, 1);
      }
   }
}

void utils::removeTrailingSpacesTabs(string &line)
{
   if (!line.empty()) {
      while (line[line.size() - 1] == ' ' ||
             line[line.size() - 1] == '\t') {
         line.erase(line.size() - 1, 1);
      }
   }
}

void utils::removeLeadingTrailingSpacesTabs(string &line)
{
   removeLeadingSpacesTabs(line);
   removeTrailingSpacesTabs(line);
}

void utils::replaceCommasBySpaces(string &line)
{
   size_t pos;
   while ((pos = line.find(string(","))) != string::npos) {
      line.replace(pos, 1, " ");
   }
}

void utils::removeReturns(string &line)
{
   size_t pos;
   while ((pos = line.find(string("\r"))) != string::npos) {
      line.replace(pos, 1, "");
   }
}

// function to split-up strings, to a vector of strings, using a delimiter
void utils::tokenize(const std::string &str,
                     std::vector<std::string> &tokens,
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
   for (size_t i = 0; i < input.length(); ++i) {
      input[i] = tolower(input[i]);
   }
}

void utils::capitalize(std::string &input)
{
   for (size_t i = 0; i < input.length(); ++i) {
      input[i] = toupper(input[i]);
   }
}
