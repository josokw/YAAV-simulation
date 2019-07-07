#include "INIreader.h"
#include "stringExt.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace {
/// String format ".....".
/// Pre-condition: no leading and trailing spaces or tabs.
void processEscChars(string &String)
{
   if (String.size() > 1 && String[0] == '"' &&
       String[String.size() - 1] == '"') {
      String.erase(0, 1);
      String.erase(String.size() - 1, 1);
      // Process escape chars
      size_t Index = 0;
      while (Index < String.size() - 1) {
         // Check for escape char
         if (String[Index] == '\\') {
            switch (String[Index + 1]) {
               case '\\':
                  String[Index] = '\\';
                  String.erase(Index + 1, 1);
                  break;
               case '"':
                  String[Index] = '"';
                  String.erase(Index + 1, 1);
                  break;
               case 'n':
                  String[Index] = '\n';
                  String.erase(Index + 1, 1);
                  break;
               case 't':
                  String[Index] = '\t';
                  String.erase(Index + 1, 1);
                  break;
               default:
                  // Remove '\' char
                  String.erase(Index, 1);
                  break;
            }
         }
         ++Index;
      }
   }
}
} // namespace

ostream &operator<<(ostream &os, const utils::INIreader &iniReader)
{
   auto iterMap = iniReader.m_INImap.begin();
   while (iterMap != iniReader.m_INImap.end()) {
      auto iterStrings = (*iterMap).second.begin();
      while (iterStrings != (*iterMap).second.end()) {
         os << (*iterMap).first << " = " << (*iterStrings) << endl;
         ++iterStrings;
      }
      ++iterMap;
   }
   return os;
}

const std::string utils::INIreader::m_CommentSeperator("//");

utils::INIreader::~INIreader() {}

void utils::INIreader::setFileName(const string &fileName)
{
   m_fileName = fileName;
}

void utils::INIreader::init()
{
   m_INIfile.open(m_fileName.c_str());
   if (!m_INIfile.good()) {
      ostringstream Xtext;
      Xtext << "[INIreader] can't open file '" << m_fileName << "'"
            << ends;
      throw std::runtime_error(Xtext.str());
   }
   fillINImap();
   m_INIfile.close();
}

void utils::INIreader::GetData(const string &dataName, string &Data) const
{
   Data = (*findDataValue(dataName)).second[0];
   processEscChars(Data);
}

void utils::INIreader::GetData(const char *dataName, string &Data) const
{
   GetData(string(dataName), Data);
}

void utils::INIreader::GetData(const string &dataName,
                               vector<string> &Data) const
{
   Data = (*findDataValue(dataName)).second;
   auto I = Data.begin();
   while (I != Data.end()) {
      processEscChars(*I);
      ++I;
   }
}

void utils::INIreader::clear()
{
   m_INImap.clear();
}

void utils::INIreader::fillINImap(std::istream &InputStream,
                                  const string &EndINIline)
{
   string RHSline;
   vector<string> RHSlines;
   string LHSline;
   string PreviousLHSline;
   bool MustBeAddedToMap(false);
   string PrefixdataName;
   bool INIisEnded = false;

   while (!InputStream.eof() && !INIisEnded) {
      // read line by line
      getline(InputStream, m_line);
      ++m_lineNumber;
      // if DOS format: remove \r
      utils::removeReturns(m_line);
      removeComment();
      utils::removeLeadingTrailingSpacesTabs(m_line);
      if (!m_line.empty()) {
         INIisEnded = (m_line == EndINIline);
         if (!INIisEnded && lineIsSection()) {
            GetSectionData(MustBeAddedToMap, PrefixdataName);
            PreviousLHSline = "";
         } else {
            if (!INIisEnded && MustBeAddedToMap) {
               GetRHSassignment(RHSline);
               utils::replaceCommasBySpaces(RHSline);
               GetLHSassignment(LHSline);
               if (LHSline.empty()) {
                  LHSline = PreviousLHSline;
                  RHSlines.push_back(RHSline);
               } else {
                  PreviousLHSline = LHSline;
                  RHSlines.clear();
                  RHSlines.push_back(RHSline);
               }
               if (!PrefixdataName.empty()) {
                  LHSline = PrefixdataName + "." + LHSline;
               }
               m_INImap[LHSline] = RHSlines;
            }
         }
      }
   }
}

void utils::INIreader::AddToINImap(const std::string &Key,
                                   const std::string &Value)
{
   vector<string> Values;
   Values.push_back(Value);
   m_INImap[Key] = Values;
}

//-------------------------------------------------------------------------
//protected

utils::INIreader::INIreader()
   : m_fileName("")
   , m_INIfile()
   , m_line("")
   , m_lineNumber(0)
   , m_INImap()
{
}

//-------------------------------------------------------------------------
//private

void utils::INIreader::fillINImap()
{
   string RHSline;
   vector<string> RHSlines;
   string LHSline;
   string PreviousLHSline;
   bool MustBeAddedToMap(false);
   string PrefixdataName;

   while (!m_INIfile.eof()) {
      // read line by line
      getline(m_INIfile, m_line);
      ++m_lineNumber;
      // if DOS format: remove \r
      utils::removeReturns(m_line);
      removeComment();
      utils::removeLeadingTrailingSpacesTabs(m_line);
      if (!m_line.empty()) {
         if (lineIsSection()) {
            GetSectionData(MustBeAddedToMap, PrefixdataName);
            PreviousLHSline = "";
         } else {
            if (MustBeAddedToMap) {
               GetRHSassignment(RHSline);
               utils::replaceCommasBySpaces(RHSline);
               GetLHSassignment(LHSline);
               if (LHSline.empty()) {
                  LHSline = PreviousLHSline;
                  RHSlines.push_back(RHSline);
               } else {
                  PreviousLHSline = LHSline;
                  RHSlines.clear();
                  RHSlines.push_back(RHSline);
               }
               if (!PrefixdataName.empty()) {
                  LHSline = PrefixdataName + "." + LHSline;
               }
               m_INImap[LHSline] = RHSlines;
            }
         }
      }
   }
}

void utils::INIreader::GetRHSassignment(string &RHSline) const
{
   size_t pos(m_line.find("="));
   if (pos == string::npos) {
      ostringstream Xtext;
      Xtext << "[INIreader] syntax error in line " << m_lineNumber;
      Xtext << ": '" << m_line << "', could not find =" << ends;
      throw std::runtime_error(Xtext.str());
   }
   RHSline = m_line;
   RHSline.erase(0, pos + 1);
   utils::removeLeadingTrailingSpacesTabs(RHSline);
}

void utils::INIreader::GetLHSassignment(string &LHSline) const
{
   size_t pos(m_line.find("="));
   if (pos == string::npos) {
      ostringstream Xtext;
      Xtext << "[INIreader] syntax error in line " << m_lineNumber << ": '"
            << m_line << "', could not find =" << ends;
      throw std::runtime_error(Xtext.str());
   }
   LHSline = m_line;
   LHSline.erase(pos);
   utils::removeLeadingTrailingSpacesTabs(LHSline);
}

void utils::INIreader::removeComment()
{
   size_t pos = m_line.find(m_CommentSeperator);
   if (pos != string::npos) {
      m_line.erase(pos);
   }
}

bool utils::INIreader::lineIsSection() const
{
   // pre-condition: line contains no leading and trailing spaces and tabs
   return (m_line[0] == '[' && m_line[m_line.size() - 1] == ']');
}

void utils::INIreader::GetSectionData(bool &MustBeAddedToMap,
                                      string &PrefixdataName)
{
   // line must be a section
   string Buffer(m_line);
   // remove '[' and ']'
   Buffer.erase(0, 1);
   Buffer.erase(Buffer.size() - 1, 1);
   utils::removeLeadingTrailingSpacesTabs(Buffer);
   // create IDline
   string IDline(Buffer);
   // size_t pos = Buffer.find(':');
   // IDline.assign(Buffer, 0, pos);
   utils::removeLeadingTrailingSpacesTabs(IDline);

   MustBeAddedToMap = false;
   istringstream IDBuffer(IDline.c_str());
   string ID;
   while (!IDBuffer.fail() && !MustBeAddedToMap) {
      IDBuffer >> ID;
      // m_ID = ID;
      // MustBeAddedToMap = (ID == m_ID);
      MustBeAddedToMap = true;
   }
   if (MustBeAddedToMap) {
      // create prefixdataName
      PrefixdataName.assign(Buffer, 0, Buffer.size());
      // utils::removeLeadingTrailingSpacesTabs(PrefixdataName);
   } else {
      PrefixdataName = "";
   }
}

utils::INIreader::INImap_const_iter_t
utils::INIreader::findDataValue(const string &dataName) const
{
   auto iter = m_INImap.find(dataName);
   if (iter == m_INImap.end()) {
      ostringstream Xtext;
      Xtext << "[INIreader] could not find '" << dataName << "'" << ends;
      throw std::runtime_error(Xtext.str());
   }
   return iter;
}

bool utils::INIreader::dataNameIsUnique(const string &dataName) const
{
   return m_INImap.find(dataName) == m_INImap.end();
}
