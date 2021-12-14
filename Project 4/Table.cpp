//
//  Table.cpp
//  Project4
//
//

#include "Table.h"


Table::Table(std::string keyColumn, const std::vector<std::string>& columns)
{
    //set all the pointers in the hash table to null
    for (int i=0; i<1000;i++)
    {
        HashTable[i]=nullptr;
    }
    //set member variables
    m_columns=columns;
    m_keyColumn=keyColumn;
    columnNum=columns.size();
    keyIndex=0;
    for (int i=0; i<columnNum; i++)
    {
        if (m_keyColumn==m_columns[i])
        {
            keyIndex=i;
        }
    }
}

Table::~Table()
{
    for (int i=0; i<1000;i++)
    {
        if (HashTable[i]!=nullptr)
        {
            delete HashTable[i];
        }
    }
}

bool Table::good() const
{
    //check that column vector isn't empty
    if (columnNum==0 )
        return false;
    
    //check that column vector doesn't contain empty strings
    for (std::vector<std::string>::const_iterator it = m_columns.cbegin() ; it != m_columns.cend(); ++it)
    {
        if (*it=="")
            return false;
    }

    //check that keyColumn is one of the column names
    int j=0;
    for (std::vector<std::string>::const_iterator it = m_columns.cbegin() ; it != m_columns.cend(); ++it)
    {
        if (*it==m_keyColumn)
            j++;
    }
    
    if (j!=1)
        return false;
    
    //check that column vector doesn't contain duplicate strings
    for (std::vector<std::string>::const_iterator i = m_columns.cbegin() ; i != m_columns.cend(); ++i)
    {
        int repeats=0;
        for (std::vector<std::string>::const_iterator j = m_columns.cbegin() ; j != m_columns.cend(); ++j)
        {
            if (*i==*j)
                repeats++;
        }
        //should be 1 because it will iterate for itself
        if (repeats!=1)
            return false;
    }
    
    return true;
}

//Insert a record into the database. The parameter is a string with the fields of the record in a format described below. If the string has the correct number of fields for the table, insert a record with those fields into the table and return true; otherwise, leave the table unchanged and return false.
bool Table::insert(const std::string& recordString)
{
    //check that it was called on a valid object
    if (!good())
        return false;
    std::vector<std::string> v;
    int size=0;
    StringParser parser(recordString);
    std::string s;
    //convert the string parameter into a vector of strings
    while (parser.getNextField(s)==true)
    {
        size++;
        v.push_back(s);
    }
    //return false is the string parameter has the incorrect number of fields for the table
    if (size!=columnNum)
    {
        return false;
    }
    //find correct bucket
    std::string stringKey=v[keyIndex];
    unsigned int x=(std::hash<std::string>()(stringKey))%1000;
    //if array index is empty create new 2D vector there. Push back the vector of strings
    if (HashTable[x]==nullptr)
    {HashTable[x]=new std::vector<std::vector<std::string>>();}
    HashTable[x]->push_back(v);
    
    return true;
}

//Replace the value in the second parameter with a vector containing as many elements as there are records in the table whose key field is a string equal to the value of the first parameter. Each of those elements is one of the matching records, represented as a vector whose elements are the fields of that record. The records placed in the vector don't have to be in any particular order.
void Table::find(std::string key, std::vector<std::vector<std::string>>& records) const
{
    //check that it was called on a valid object
    if (!good())
        return
    records.clear();
    //find correct bucket and return if its empty
    unsigned int x=(std::hash<std::string>()(key))%1000;
    if (HashTable[x]==nullptr)
    {
        return;
    }
    //get number of entries for this bucket
    int entries=HashTable[x]->size();
    
    records.resize(entries);  // grid now has number of empty rows equal to number of entries
    for (int i = 0; i < entries; i++)
        records[i].resize(columnNum);  // row i now has columnNum columns
    //set records equal to the 2D vector in correct bucket
    records=*HashTable[x];

}

//Replace the value in the second parameter with a vector containing as many elements as there are records in the table that satisfy the query. Each of those elements is one of the matching records, represented as a vector whose elements are the fields of that record. The function returns 0 if it succeeds without any problems.
int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const
{
    if (!good())
        return -1;
    //clear the vector parameter
    records.clear();
    //create new vector and push back the contents of the query term
    std::vector<std::string> v;
    int size=0;
    StringParser parser(query);
    std::string s;
    while (parser.getNextField(s)==true)
    {
        size++;
        v.push_back(s);
    }
    //check that the query has three tokens
    if (size!=3)
    {
        return -1;
    }
    
    //check that the first token is a column name
    int j=0;
    for (int i=0; i<columnNum; i++)
        {
            if (m_columns[i]==v[0])
            j++;
        }
    if (j!=1)
    {
        return -1;
    }
    //check that none of the tokens are the empty string
    for (int i=0; i<3; i++)
    {
        if (v[i]=="")
        {
            return -1;
        }
    }
    //check that the second token is a comparison operator
    if (v[1]!="<"&&v[1]!="<="&&v[1]!=">"&&v[1]!=">="&&v[1]!="!="&&v[1]!="=="&&v[1]!="="&&v[1]!="LT"&&v[1]!="LE"&&v[1]!="GT"&&v[1]!="GE"&&v[1]!="NE"&&v[1]!="EQ"&&v[1]!="lT"&&v[1]!="Lt"&&v[1]!="lt"&&v[1]!="Le"&&v[1]!="lE"&&v[1]!="le"&&v[1]!="Ge"&&v[1]!="gE"&&v[1]!="ge"&&v[1]!="Ne"&&v[1]!="nE"&&v[1]!="ne"&&v[1]!="Eq"&&v[1]!="eQ"&&v[1]!="eq"&&v[1]!="gT"&&v[1]!="Gt"&&v[1]!="gt")
    {return -1;}
    double token3=0;
    bool numerical=false;
    //check that if its a numerical comparison operator the third token is a number in proper form
    if (v[1]=="LT"||v[1]=="LE"||v[1]=="GT"||v[1]=="GE"||v[1]=="NE"||v[1]=="EQ"||v[1]=="lT"||v[1]=="Lt"||v[1]=="lt"||v[1]=="Le"||v[1]=="lE"||v[1]=="le"||v[1]=="Ge"||v[1]=="gE"||v[1]=="ge"||v[1]=="Ne"||v[1]=="nE"||v[1]=="ne"||v[1]=="Eq"||v[1]=="eQ"||v[1]=="eq"||v[1]=="gT"||v[1]=="Gt"||v[1]=="gt")
    {
        if (stringToDouble(v[2], token3)!=true)
        {return -1;}
        numerical=true;
    }
    
    
    //find index of query
    int queryIndex=0;
    for (int i=0; i<columnNum; i++)
    {
        if (v[0]==m_columns[i])
        {
            queryIndex=i;
        }
    }
    
    //look through every entry to check query
    int incorrect=0;
    for (int i=0; i<1000;i++)
    {
        if (HashTable[i]!=nullptr)
        {
            //set new vector of vectors equal to the bucket contents (to make code easier)
            std::vector<std::vector<std::string>> arrayRecords;
            int entries=HashTable[i]->size();
            arrayRecords.resize(entries);  // grid now has number of empty rows equal to number of entries
            for (int i = 0; i < entries; i++)
                arrayRecords[i].resize(columnNum);  // row i now has columnNum columns
            arrayRecords=*HashTable[i];
            //look through new 2D vector
            for (int i = 0; i < entries; i++)
            {
                double stringValue=0.0;
                //if its a numerical comprison and the item we're looking at isn't in proper form for a number, mark as incorrect
                if (numerical==true && stringToDouble(arrayRecords[i][queryIndex], stringValue)==false)
                {
                    incorrect++;
                }
                //check if the query is true for the item we're looking at (for numerical comparison)
                //if so add it to the vector
                else if (numerical==true)
                {
                    if ((v[1]=="LT"||v[1]=="lT"||v[1]=="Lt"||v[1]=="lt") && stringValue<token3)
                        records.push_back(arrayRecords[i]);
                    else if ((v[1]=="LE"||v[1]=="Le"||v[1]=="lE"||v[1]=="le") && stringValue<=token3)
                        records.push_back(arrayRecords[i]);
                    else if ((v[1]=="GE"||v[1]=="Ge"||v[1]=="gE"||v[1]=="ge") && stringValue>=token3)
                        records.push_back(arrayRecords[i]);
                    else if ((v[1]=="GT"||v[1]=="Gt"||v[1]=="gT"||v[1]=="gt")&& stringValue>token3)
                        records.push_back(arrayRecords[i]);
                    else if ((v[1]=="NE"||v[1]=="Ne"||v[1]=="nE"||v[1]=="ne") && stringValue!=token3)
                        records.push_back(arrayRecords[i]);
                    else if ((v[1]=="EQ"||v[1]=="Eq"||v[1]=="eQ"||v[1]=="eq") && stringValue==token3)
                        records.push_back(arrayRecords[i]);
                }
                //check if the query is true for the item we're looing at (for string comparison operator)
                //if so add it to the vector
                else
                {
                    if (v[1]=="<" && arrayRecords[i][queryIndex]<v[2])
                        records.push_back(arrayRecords[i]);
                    else if (v[1]=="<=" && arrayRecords[i][queryIndex]<=v[2])
                        records.push_back(arrayRecords[i]);
                    else if (v[1]==">" && arrayRecords[i][queryIndex]>v[2])
                        records.push_back(arrayRecords[i]);
                    else if (v[1]==">=" && arrayRecords[i][queryIndex]>=v[2])
                        records.push_back(arrayRecords[i]);
                    else if (v[1]=="!=" && arrayRecords[i][queryIndex]!=v[2])
                        records.push_back(arrayRecords[i]);
                    else if ((v[1]=="=="||v[1]=="=")&& arrayRecords[i][queryIndex]==v[2])
                        records.push_back(arrayRecords[i]);
                }
            }
            
        }
    }
    //return number of records who's value is not in correct form for numerical operator
    return incorrect;
}

//If the first argument to the following function is string that is a number in proper form, the function returns true and sets the second parameter to the number represented by the string; otherwise, it returns false
bool Table::stringToDouble(std::string s, double& d) const
    {
        char* end;
        d = std::strtof(s.c_str(), &end);
        return end == s.c_str() + s.size()  &&  !s.empty();
    }

//string parser implementations
bool StringParser::getNextField(std::string& fieldText)
{
    m_start = m_text.find_first_not_of(" \t\r\n", m_start);
    if (m_start == std::string::npos)
    {
        m_start = m_text.size();
        fieldText = "";
        return false;
    }
    if (m_text[m_start] != '\'')
    {
        size_t end = m_text.find_first_of(" \t\r\n", m_start+1);
        fieldText = m_text.substr(m_start, end-m_start);
        m_start = end;
        return true;
    }
    fieldText = "";
    for (;;)
    {
        m_start++;
        size_t end = m_text.find('\'', m_start);
        fieldText += m_text.substr(m_start, end-m_start);
        m_start = (end != std::string::npos ? end+1 : m_text.size());
        if (m_start == m_text.size()  ||  m_text[m_start] != '\'')
            break;
        fieldText += '\'';
    }
    return true;
}
