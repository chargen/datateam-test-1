#include "./analyze.h"
#include "./tokenize.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include "./types.h"

typedef std::ofstream usedStreamType;

// implementation of AVG
// col1 is allways the grouping column
void doAvg(Indexed* indexed, int col1, int col2, int colType1, usedStreamType& output){
  
  const PairIndex* index = indexed->getIndex(col1, col2);
  
  if (!index){
    std::cout << "index missing! " << col1 << " " << col2 << "\n";
    return;
  };

  PairIndex::const_iterator it = index->begin();
  while (it != index->end()){
    double value = 0;
    double accValue = 0;
    double cnt = 0;
    
    // groyp by name
    int name = it->first;

    PairIndexValue* piv = it->second;

    //loop over all entries in the 2nd column
    PairIndexValue::const_iterator ivIt = piv->begin();
    while (ivIt != piv->end()){
      accValue += (ivIt->first * ivIt->second);
      cnt += ivIt->second;
      ivIt++;
    };
    
    // this could trigger some problems when we have millions of records
    value = round(accValue / cnt);

    std::cout << typedValue(name, colType1) << ": " << value << "\n";
    output    << typedValue(name, colType1) << ": " << value << "\n";

    it++;
  };
  
};

// implementation of MIN
void doMin(Indexed* indexed, int col1, int col2, int colType1, usedStreamType& output){
  
  const PairIndex* index = indexed->getIndex(col1, col2);
  
  if (!index){
    std::cout << "index missing! " << col1 << " " << col2 << "\n";
    return;
  };
  
  PairIndex::const_iterator it = index->begin();
  while (it != index->end()){
    int name = it->first;

    PairIndexValue* piv = it->second;

    //get the lowest with begin
    PairIndexValue::const_iterator ivIt = piv->begin();

    std::cout << typedValue(name, colType1) << ": " << ivIt->first << "\n";
    output    << typedValue(name, colType1) << ": " << ivIt->first << "\n";

    it++;
  };
};

// implementation of MAX
void doMax(Indexed* indexed, int col1, int col2, int colType1, usedStreamType& output){
  
  const PairIndex* index = indexed->getIndex(col1, col2);
  
  if (!index){
    std::cout << "index missing! " << col1 << " " << col2 << "\n";
    return;
  };
  
  PairIndex::const_iterator it = index->begin();
  while (it != index->end()){
    int name = it->first;

    PairIndexValue* piv = it->second;

    //get the highest with rbegin
    PairIndexValue::const_reverse_iterator ivIt = piv->rbegin();

    std::cout << typedValue(name, colType1) << ": " << ivIt->first << "\n";
    output    << typedValue(name, colType1) << ": " << ivIt->first << "\n";

    it++;
  };
  
};



// read a file with queries
// parse the queries
// and output to file as well as stdout
void analyze(Indexed* indexed, std::string queryFilename, std::string outputFilename){
  
  std::string line;
  std::ifstream queryfile(queryFilename.c_str());
  
  std::ofstream outputfile(outputFilename.c_str());
  if (!outputfile.is_open()){
    std::cout << "could not open output file\n";
    return;
  };
  
  
  const Rows* rows = indexed->rows;
  
  
  if (queryfile.is_open()){
    
    // read all the lines
    while ( getline (queryfile, line) ) {
      
      Tokens t = tokenize(line);
      
      bool valid = true;
      if (t.size() < 3){
        valid = false;
      };
      
      int colNum1 = 0;
      int colType1 = 0;
      int colNum2 = 0;
      
      if (valid){
        
        ColsByName::const_iterator colIt = rows->header.find(t[1]);
        if (colIt == rows->header.end()){
          std::cout << "column: " << t[1] << " not found!\n";
          valid = false;
          
        }else{
          
          colNum2 = colIt->second.pos;
          
          if (!typeCanAggregate(colIt->second.type)){
            std::cout << "can not perform: " << t[0] << " over " << t[1] << " of type " <<  typeName(colIt->second.type)  << "\n";
            valid = false;
            
          };
        };
        
        colIt = rows->header.find(t[2]);
        if (colIt == rows->header.end()){
          std::cout << "column: " << t[2] << " not found!\n";
          valid = false;
          
        }else{
          colNum1 = colIt->second.pos;
          colType1 = colIt->second.type;
        };
        
      };
      
      if (valid){
        // output to file and std out
        std::cout  << t[0] << " " << t[1] << " GROUPED BY " << t[2] << "\n";
        outputfile << t[0] << " " << t[1] << " GROUPED BY " << t[2] << "\n";
          
        if (t[0] == "AVG"){
          doAvg(indexed, colNum1, colNum2, colType1, outputfile);
          
        }else if (t[0] == "MIN"){
          doMin(indexed, colNum1, colNum2, colType1, outputfile);
          
        }else if (t[0] == "MAX"){
          doMax(indexed, colNum1, colNum2, colType1, outputfile);
          
        }else{
          std::cout << "unknown aggregate function: " << t[0] << "\n";
          
        };
        
        // new line
        std::cout  << "\n";
        outputfile << "\n";
        
      };
      
      
      
    };
    
  };
      
  outputfile.close();
  
};
