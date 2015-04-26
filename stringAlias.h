#ifndef STRINGALIAS_H_INCLUDED
#define STRINGALIAS_H_INCLUDED

#include <string>

/*

consider it a mini normalization
strings are not stored in the data structure directly
instead they get a int alias

*/

int getStringAlias(std::string&);
std::string getStringFromAlias(int i);

#endif