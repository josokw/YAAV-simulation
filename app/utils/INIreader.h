#ifndef UTILS_INIREADER_H
#define UTILS_INIREADER_H

#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace utils {
/// Class 'INIreader' opens and reads an '.ini' file, and stores
/// ini-data items (unique identifiers) and corresponding values into
/// an internal map (all data in string format).
/// This map can be consulted by client code for initialising var's.
/// The client code is responsible for converting the string format stored
/// in the internal map to the required type by overloading the input
/// stream operator for the corresponding type.
///
/// INIreader is implemented according to the singleton pattern.
///
/// Example contents of an '.ini' file:
/// <pre> //----------------------------------------------------
/// RoboCup.ini [visualiser.ball] RGBA   = 1, 0.5, 0, 0
/// Radius = 0.1
///
/// [visualiser.goal]
/// TeamRGBA   = 1, 1, 0, 0
/// OppoRGBA   = 0, 0, 1, 0
///
/// [visualiser.command]
/// Line      = "prog1 prog1 -p"
/// //------------------------------------------------ eof RoboCup.ini
/// </pre>
/// The stored data items in the internal map:
/// <pre>
/// visualiser.ball.RGBA
/// visualiser.ball.Radius
/// visualiser.goal.TeamRGBA
/// visualiser.goal.OppoRGBA
/// </pre>
/// DOS format files can be read, the '\r' character will be removed
/// in the lines read.
/// /short A class for '.ini' file and 'ini' data handling.
class INIreader
{
   /// Output stream operator.
   /// \param os output stream showing contents map.
   /// \param reader INIreader object.
   friend std::ostream &operator<<(std::ostream &os,
                                   const utils::INIreader &iniReader);

public:
   /// Returns a reference to an INIreader object (singleton).
   static INIreader &instance()
   {
      static INIreader iniReader;
      return iniReader;
   }
   INIreader(const INIreader &) = delete;
   INIreader &operator=(const INIreader &) = delete;
   INIreader(const INIreader &&) = delete;
   INIreader &operator=(const INIreader &&) = delete;
   ~INIreader() = default;

   /// Initialising INIreader.
   /// \exception string the .ini file can't be opened.
   void init(const std::string &fileName);
   /// Fill the internal map by an istream input.
   void fillINImap(std::istream &is, const std::string &endINIline);
   /// Add one data item to the internal map
   void AddToINImap(const std::string &key, const std::string &value);

   /// Getting the coresponding value for the requested data item.
   /// \param dataName  name of data item
   /// \param pData     pointer to memory address to store an array of type
   /// T
   /// \param nData     number of array elements to be stored
   /// \exception std::runtime_error the requested data item is not found.
   /// \exception std::runtime_error the requested data item can't be
   /// converted to type T.
   template <class T>
   void getData(const std::string &dataName, T *pData,
                const int nData = 1) const
   {
      std::istringstream buffer((*findDataValue(dataName)).second[0]);

      for (int i = 0; i < nData; i++) {
         buffer >> pData[i];
         // \todo check:  if (buffer.fail() || ((i+1) == nData &&
         // !buffer.eof()))
         if (buffer.fail()) {
            std::ostringstream Xtext;
            Xtext << "[INIreader] requested argument format for '" << dataName
                  << "'  #" << nData << " not correct" << std::ends;
            throw std::runtime_error(Xtext.str());
         }
      }
   }
   /// Getting the corresponding s(*iterMap).second.begin();tring for the
   /// requested data item. \param dataName name of data item \param Data
   /// reference to store a string (do not use a pointer) \exception string
   /// the requested data item is not found.
   void getData(const std::string &dataName, std::string &Data) const;
   /// Getting the corresponding string for the requested data item.
   /// \param dataName name of data item
   /// \param Data reference to store a string (do not use a pointer)
   /// \exception string the requested data item is not found.
   /// \todo Function necessarry?
   void getData(const char *dataName, std::string &data) const;
   /// Getting the corresponding string vector for the requested data item.
   /// \param dataName name of data itemDataName
   /// \param Data reference to store a vector of strings (do not use a
   /// pointer) \exception the requested data item is not found.
   void getData(const std::string &dataName,
                std::vector<std::string> &data) const;
   /// Getting the corresponding string vector for the requested data item.
   /// \param dataName name of data item
   /// \param data reference to store a vector of strings (do not use a
   /// pointer) \exception the requested data item is not found. \todo JO
   /// \todo Function necessarry?
   void getData(const char *dataName, std::vector<std::string> dData) const;
   /// Clear internal map.
   void clear();

protected:
   INIreader();

private:
   using INImap_t = std::map<std::string, std::vector<std::string>>;
   using INImap_const_iter_t = INImap_t::const_iterator;

   const static std::string commentSeperator_s;
   std::string fileName_;
   std::ifstream INIfile_;
   std::string line_;
   int lineNumber_;

public:
   /// Internal map <string, vector<string>> for storing unique data item
   /// names and their corresponding values (all in string format).
   INImap_t INImap_;

private:
   void fillINImap();

   /// Removing comment part out of input string.
   void removeComment();

   /// Getting the right hand site string of an assignment statement,
   /// syntax: <LHS> + '=' + <RHS>.
   /// \param RHSline  string containing RHS of the assignment statement.
   /// \exception  a '=' isn't found in line read.
   void getRHSassignment(std::string &RHSline) const;

   /// Getting the left hand site string of an assignment statement,
   /// syntax: <LHS> + '=' + <RHS>.
   /// \param RHSline  string containing LHS of the assignment statement.
   /// \exception  if a '=' isn't found in the line read.
   void getLHSassignment(std::string &LHSline) const;

   /// Checkking if line contains a section, syntax:
   /// '[' + <system ID> + ':' + <prefix data name> + ']'.
   /// \return  true if input string is a section false if not.
   bool lineIsSection() const;

   /// Parse section line and subtract data contents.
   /// \param mustBeAddedToMap indicates if the data item read must be
   /// added to the map. \param prefixdataName  string to be add as a
   /// prefix to data name read from the input file.
   void getSectionData(bool &mustBeAddedToMap, std::string &prefixdataName);

   /// Find data in internal map.
   /// \param dataName string containing name of data item.
   /// \return const_iterator to argument string in the internal map.
   /// \exception string the requested data item is not found in the
   /// internal map.
   INImap_const_iter_t findDataValue(const std::string &dataName) const;
   bool dataNameIsUnique(const std::string &dataName) const;
};
} // namespace utils

#endif
