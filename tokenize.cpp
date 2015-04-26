
#include "./tokenize.h"

// simply take a string apart into its tokens
Tokens tokenize (std::string& s){
  
  size_t l = s.length();
  std::string token;
  
  Tokens res;
  
  int i = 0;
  for (i = 0; i < l; ++i){
    if (s[i] == ' '){
      if (token.length()){
        res.push_back(token);
        token = "";
      };
    }else{
      token += s[i];
    };
  };
  if (token.length()){
    res.push_back(token);
  };
  
  return res;
  
};
