#ifndef TOKENIZE_H_INCLUDED
#define TOKENIZE_H_INCLUDED

#include <string>
#include <vector>

/*
  
  helper to cut a string apart into seperate strings
  single space is seperator
  the result is a vector of strings
  
*/

typedef std::vector<std::string> Tokens;

// simply take a string apart into its tokens
Tokens tokenize (std::string& s);

#endif