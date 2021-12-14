//
//  Table.hpp
//  Project4
//
//

#ifndef Table_h
#define Table_h
#include <string>
#include <functional>
#include <vector>
#include <cstdlib>

class Table
{
  public:
    Table(std::string keyColumn, const std::vector<std::string>& columns);
    ~Table();
    bool good() const;
    bool insert(const std::string& recordString);
    void find(std::string key, std::vector<std::vector<std::string>>& records) const;
    int select(std::string query, std::vector<std::vector<std::string>>& records) const;

      // We prevent a Table object from being copied or assigned by
      // making the copy constructor and assignment operator unavailable.
    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;
  private:
    int columnNum;
    std::vector<std::string> m_columns;
    int keyIndex;
    std::string m_keyColumn;
    std::vector<std::vector<std::string>>* HashTable[1000];
    bool stringToDouble(std::string s, double& d) const;
};

class StringParser
{
  public:
    StringParser(std::string text = "")
    {
        setString(text);
    }

    void setString(std::string text)
    {
        m_text = text;
        m_start = 0;
    }

    bool getNextField(std::string& field);

  private:
    std::string m_text;
    size_t m_start;
};

#endif /* Table_h */
