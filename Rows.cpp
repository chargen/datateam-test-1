#include "./Rows.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "./stringAlias.h"
#include "./tokenize.h"
#include "./types.h"


Rows::Rows(std::string filename){
  
  std::string line;
  std::ifstream file (filename.c_str());
  
  if (file.is_open()){
    
    Tokens names;
    Tokens types;
    
    // read column lines
    bool cont = true;
    if ( getline (file, line) ){
      names = tokenize(line);
    }else{
      cont = false;
    };
    if ( cont && getline (file, line) ){
      types = tokenize(line);
      
      ColInfo ci; // uninitialized memory
      
      int l = std::min(names.size(), types.size());
      int i = 0;
      for (i = 0; i < l; ++i){
        // some helpful debug msgs
        //std::cout << names[i] << ": " << types[i] << "\n";
        
        ci.pos = i;
        ci.name = names[i];
        ci.type = typeIdByName(types[i]);
        
        this->header.insert(ColsByName::value_type(ci.name, ci));
        this->headerByPos.push_back(ci);
      };
      
    }else{
      cont = false;
    };
    
    // read all the lines
    if ( cont ) { while ( getline (file, line) ) {
      
      Tokens values = tokenize(line);
      Row row;
      
      
      int l = std::min(values.size(), this->headerByPos.size());
      int i = 0;
      for (i = 0; i < l; ++i){
        // this could maybe move to types.h as well or better a seperate file
        // but for 2 types its alright here
        // still easy to maintain
        if (this->headerByPos[i].type == cTypeInt){
          // int
          // convert string to int
          int value = atoi( values[i].c_str() );
          row.push_back(value); // potentially a little slow
          
        }else{
          // string
          // we do not wanna save strings in out data structure
          // they are slow and they are huge
          int value = getStringAlias(values[i]);
          row.push_back(value); // potentially a little slow
        };
      };
      
      this->rowData.push_back(row); // potentially very slow
      
    }; };
    
    file.close();
    
  } else {
    std::cout << "Unable to open file"; 
    
  };
  
};


// just for debug / insights reasons
void displayRows(Rows* r){
  
  
  ColsByName::iterator it = r->header.begin();
  while (it != r->header.end()){
    
    std::cout << "column: " << it->second.name << ", pos: " << it->second.pos << ", type: " << it->second.type << "\n";
    
    it++;
  };
  
  // all rows
  rowDataType::iterator d = r->rowData.begin();
  while (d != r->rowData.end()){
    
    Row::iterator rIt = d->begin();
    while(rIt != d->end()){
      
      std::cout << " " << *rIt;
      
      rIt++;
    };
    
    std::cout << "\n";
    
    d++;
  };
  
};




