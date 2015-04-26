#ifndef INDEXED_H_INDLUCED
#define INDEXED_H_INDLUCED

#include "./Rows.h"

#include <vector>
#include <map>

// takes a parsed data pointer (Rows.h) and creates several indexes on it

// represents an entry in the index
// meaning we have so many entries with this specific value
//
// for example <5, 10> <6, 14> means we have 10 times the value 5 and 14 times the value 6
//
// all as 2nd column ofc
//
typedef std::map<int, size_t> PairIndexValue;


// essentially the index
//
// per value of column1 we have a map of column 2
//
// <1, {}>, <2, {}> we have a map for all values associated with value "1" and a map for value "2" and so on ...
//
typedef std::map<int, PairIndexValue*> PairIndex;


// this maps associates the index with its column numbers (column position)

// represents all the 2nd columns in the index per 1st column
typedef std::map<int, PairIndex*> PairIndexPerCol; 

// represents all indexes that start with the column number assoziated with the vector index
typedef std::vector<PairIndexPerCol*> PairIndexesPerCol;


class Indexed {
public:
  Indexed(Rows*);
  ~Indexed(); // we need to do a lot of clean up
  
  const Rows* rows;
  
  // access to index from outside
  const PairIndex* getIndex(int col1, int col2);
  
private:
  PairIndexesPerCol pairIndexes; // the indexes
  
  void createIndex(size_t col1, size_t col2);
  
};

#endif