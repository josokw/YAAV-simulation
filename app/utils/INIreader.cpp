#include "INIreader.h"
#include "stringExt.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {
/// str format ".....".
/// \pre: no leading and trailing spaces or tabs.
void processEscChars(std::string &str)
{
   if (str.size() > 1 && str[0] == '"' && str[str.size() - 1] == '"') {
      str.erase(0, 1);
      str.erase(str.size() - 1, 1);
      // Process escape chars
      size_t Index = 0;
      while (Index < str.size() - 1) {
         // Check for escape char
         if (str[Index] == '\\') {
            switch (str[Index + 1]) {
               case '\\':
                  str[Index] = '\\';
                  str.erase(Index + 1, 1);
                  break;
               case '"':
                  str[Index] = '"';
                  str.erase(Index + 1, 1);
                  break;
               case 'n':
                  str[Index] = '\n';
                  str.erase(Index + 1, 1);
                  break;
               case 't':
                  str[Index] = '\t';
                  str.erase(Index + 1, 1);
                  break;
               default:
                  // Remove '\' char
                  str.erase(Index, 1);
                  break;
            }
         }
         ++Index;
      }
   }
}
} // namespace

std::ostream &operator<<(std::ostream &os, const utils::INIreader &iniReader)
{
   auto iterMap = iniReader.INImap_.begin();
   while (iterMap != iniReader.INImap_.end()) {
      auto iterStrings = (*iterMap).second.begin();
      while (iterStrings != (*iterMap).second.end()) {
         os << (*iterMap).first << " = " << (*iterStrings) << std::endl;
         ++iterStrings;
      }
      ++iterMap;
   }
   return os;
}

const std::string utils::INIreader::commentSeperator_s("//");

void utils::INIreader::init(const std::string &fileName)
{
   fileName_ = fileName;
   INIfile_.open(fileName_);
   if (!INIfile_) {
      std::ostringstream Xtext;
      Xtext << "[INIreader] can't open file '" << fileName_ << "'" << std::ends;
      throw std::runtime_error(Xtext.str());
   } else {
      fillINImap();
      INIfile_.close();
   }
}

void utils::INIreader::getData(const std::string &dataName,
                               std::string &data) const
{
   data = (*findDataValue(dataName)).second[0];
   processEscChars(data);
}

void utils::INIreader::getData(const char *dataName, std::string &Data) const
{
   getData(std::string(dataName), Data);
}

void utils::INIreader::getData(const std::string &dataName,
                               std::vector<std::string> &data) const
{
   data = (*findDataValue(dataName)).second;
   auto I = begin(data);
   while (I != end(data)) {
      processEscChars(*I);
      ++I;
   }
}

void utils::INIreader::clear()
{
   INImap_.clear();
}

void utils::INIreader::fillINImap(std::istream &is,
                                  const std::string &EndINIline)
{
   std::string RHSline;
   std::vector<std::string> RHSlines;
   std::string LHSline;
   std::string PreviousLHSline;
   bool mustBeAddedToMap(false);
   std::string prefixdataName;
   bool INIisEnded = false;

   while (!is.eof() && !INIisEnded) {
      // read line by line
      getline(is, line_);
      ++lineNumber_;
      // if DOS format: remove \r
      utils::removeReturns(line_);
      removeComment();
      utils::removeLeadingTrailingSpacesTabs(line_);
      if (!line_.empty()) {
         INIisEnded = (line_ == EndINIline);
         if (!INIisEnded && lineIsSection()) {
            getSectionData(mustBeAddedToMap, prefixdataName);
            PreviousLHSline = "";
         } else {
            if (!INIisEnded && mustBeAddedToMap) {
               getRHSassignment(RHSline);
               utils::replaceCommasBySpaces(RHSline);
               getLHSassignment(LHSline);
               if (LHSline.empty()) {
                  LHSline = PreviousLHSline;
                  RHSlines.push_back(RHSline);
               } else {
                  PreviousLHSline = LHSline;
                  RHSlines.clear();
                  RHSlines.push_back(RHSline);
               }
               if (prefixdataName.empty()) {
                  LHSline = prefixdataName + "." + LHSline;
               }
               INImap_[LHSline] = RHSlines;
            }
         }
      }
   }
}

void utils::INIreader::AddToINImap(const std::string &key,
                                   const std::string &value)
{
   std::vector<std::string> values;
   values.push_back(value);
   INImap_[key] = values;
}

//-------------------------------------------------------------------------
// protected

utils::INIreader::INIreader()
   : fileName_{""}
   , INIfile_{}
   , line_{""}
   , lineNumber_{0}
   , INImap_{}
{
}

//-------------------------------------------------------------------------
// private

void utils::INIreader::fillINImap()
{
   std::string RHSline;
   std::vector<std::string> RHSlines;
   std::string LHSline;
   std::string PreviousLHSline;
   bool mustBeAddedToMap(false);
   std::string prefixdataName;

   while (not INIfile_.eof()) {
      // read line by line
      getline(INIfile_, line_);
      ++lineNumber_;
      // if DOS format: remove \r
      utils::removeReturns(line_);
      removeComment();
      utils::removeLeadingTrailingSpacesTabs(line_);
      if (!line_.empty()) {
         if (lineIsSection()) {
            getSectionData(mustBeAddedToMap, prefixdataName);
            PreviousLHSline = "";
         } else {
            if (mustBeAddedToMap) {
               getRHSassignment(RHSline);
               utils::replaceCommasBySpaces(RHSline);
               getLHSassignment(LHSline);
               if (LHSline.empty()) {
                  LHSline = PreviousLHSline;
                  RHSlines.push_back(RHSline);
               } else {
                  PreviousLHSline = LHSline;
                  RHSlines.clear();
                  RHSlines.push_back(RHSline);
               }
               if (not prefixdataName.empty()) {
                  LHSline = prefixdataName + "." + LHSline;
               }
               INImap_[LHSline] = RHSlines;
            }
         }
      }
   }
}

void utils::INIreader::getRHSassignment(std::string &RHSline) const
{
   size_t pos(line_.find("="));
   if (pos == std::string::npos) {
      std::ostringstream Xtext;
      Xtext << "[INIreader] syntax error in line " << lineNumber_;
      Xtext << ": '" << line_ << "', could not find =" << std::ends;
      throw std::runtime_error(Xtext.str());
   }
   RHSline = line_;
   RHSline.erase(0, pos + 1);
   utils::removeLeadingTrailingSpacesTabs(RHSline);
}

void utils::INIreader::getLHSassignment(std::string &LHSline) const
{
   size_t pos(line_.find("="));
   if (pos == std::string::npos) {
      std::ostringstream Xtext;
      Xtext << "[INIreader] syntax error in line " << lineNumber_ << ": '"
            << line_ << "', could not find =" << std::ends;
      throw std::runtime_error(Xtext.str());
   }
   LHSline = line_;
   LHSline.erase(pos);
   utils::removeLeadingTrailingSpacesTabs(LHSline);
}

void utils::INIreader::removeComment()
{
   size_t pos = line_.find(commentSeperator_s);
   if (pos != std::string::npos) {
      line_.erase(pos);
   }
}

bool utils::INIreader::lineIsSection() const
{
   // pre-condition: line contains no leading and trailing spaces and tabs
   return (line_[0] == '[' && line_[line_.size() - 1] == ']');
}

void utils::INIreader::getSectionData(bool &mustBeAddedToMap,
                                      std::string &prefixdataName)
{
   // line must be a section
   std::string buffer(line_);
   // remove '[' and ']'
   buffer.erase(0, 1);
   buffer.erase(buffer.size() - 1, 1);
   utils::removeLeadingTrailingSpacesTabs(buffer);
   // create IDline
   std::string IDline(buffer);
   // size_t pos = buffer.find(':');
   // IDline.assign(buffer, 0, pos);
   utils::removeLeadingTrailingSpacesTabs(IDline);

   mustBeAddedToMap = false;
   std::istringstream IDBuffer(IDline);
   std::string ID;
   while (!IDBuffer.fail() && !mustBeAddedToMap) {
      IDBuffer >> ID;
      // m_ID = ID;
      // mustBeAddedToMap = (ID == m_ID);
      mustBeAddedToMap = true;
   }
   if (mustBeAddedToMap) {
      // create prefixdataName
      prefixdataName.assign(buffer, 0, buffer.size());
      // utils::removeLeadingTrailingSpacesTabspPrefixdataName);
   } else {
      prefixdataName = "";
   }
}

utils::INIreader::INImap_const_iter_t
utils::INIreader::findDataValue(const std::string &dataName) const
{
   auto iter = INImap_.find(dataName);
   if (iter == INImap_.end()) {
      std::ostringstream Xtext;
      Xtext << "[INIreader] could not find '" << dataName << "'" << std::ends;
      //throw std::runtime_error(Xtext.str());
   }
   return iter;
}

bool utils::INIreader::dataNameIsUnique(const std::string &dataName) const
{
   return INImap_.find(dataName) == end(INImap_);
}
