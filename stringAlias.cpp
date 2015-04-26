#include "./stringAlias.h"
#include <map>
#include <iostream>

int stringAliasCounter = 1;

typedef std::map< std::string, int > stringAliasMapType;
stringAliasMapType stringAliasMap;

// this can not be a vector because of performance reasons
typedef std::map< int, std::string > stringAliasReverseMapType;
stringAliasReverseMapType stringAliasReverseMap;

int getStringAlias(std::string& s){
  
  //std::cout << s << " ";
  
  stringAliasMapType::iterator it = stringAliasMap.find(s);
  if (it == stringAliasMap.end()){
    // this string hasnt got an alias yet
    int alias = stringAliasCounter;
    ++stringAliasCounter;
    stringAliasMap.insert(stringAliasMapType::value_type(s, alias));
    stringAliasReverseMap.insert(stringAliasReverseMapType::value_type(alias, s));
    
    //std::cout << "new " << alias << "\n";
    return alias;
    
  }else{
    // found it
    int res = it->second;
    //std::cout << "found " << res << "\n";
    return res;
    
  };
  
};

// reverse of the above
std::string getStringFromAlias(int i){
  
  stringAliasReverseMapType::iterator it = stringAliasReverseMap.find(i);
  if (it != stringAliasReverseMap.end()){
    return it->second;
  };
  
  return "string alias not found";
};
