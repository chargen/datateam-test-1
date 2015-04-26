
#include "./types.h"

// a collection of functions that makes managing different types a little more easy

// types:
// 0 int
// 1 string

//const int cTypeInt = 0;
//const int cTypeString = 1;

// can we aggregate over a col of this type
bool typeCanAggregate(int type){
  
  if (type == cTypeInt){
    return true;
  };
  
  return false;
  
}

// give the type name by id
std::string typeName(int type){
  
  if (type == cTypeInt){
    return "integer";
  };
  
  if (type == cTypeString){
    return "string";
  };
  
  return "unknown";
  
}

// returns the type id by type name
// used by parsing
int typeIdByName(std::string name){
  if (name == "string"){
    return cTypeString;
  };
  
  // shortcut
  //consider everything to be int unless its string
  return cTypeInt;
};


// return the value in a readable form considering the type
std::string typedValue(int value, int type){
  
  if (type == cTypeInt){
    
    std::string result;
    std::ostringstream convert;   // stream used for the conversion
    convert << value; 
    result = convert.str();
    return result;
  };
  
  if (type == cTypeString){
    return getStringFromAlias(value);
  };
  
  return "unknown";
  
}

