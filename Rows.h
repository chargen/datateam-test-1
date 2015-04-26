#ifndef ROWS_H_DEFINED
#define ROWS_H_DEFINED

#include <string>
#include <vector>
#include <map>

/*

represents the raw data read from the file
row by row
plus header information

*/


// i chose a vector over the obvious std::deque because the import speed was explicitly
// marked as non critical
typedef std::vector< int > dataType;

// header info for one column
class ColInfo {
public:
  size_t pos;       // position of the column
  int type;         // type: 0 int; 1 string
  std::string name; // name of the column
};

typedef std::map<std::string, ColInfo> ColsByName;
typedef std::vector<ColInfo> ColsByPos;

typedef dataType Row; // i suspect this type could become more complex

typedef std::vector<Row> rowDataType;

// represents all the info parsed from a file
// stored in a efficiatly readable format
class Rows{
public:
  Rows(std::string);
  
  ColsByName header;
  ColsByPos headerByPos;
  rowDataType rowData;
};


// debug
void displayRows(Rows* r);

#endif