#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <string>
#include <sstream>

#include "./stringAlias.h"

// a collection of functions that makes managing different types a little more easy

// types:
// 0 int
// 1 string

const int cTypeInt = 0;
const int cTypeString = 1;

// can we aggregate over a col of this type
bool typeCanAggregate(int type);

// give the type name by id
std::string typeName(int type);

// returns the type id by type name
// used by parsing
int typeIdByName(std::string name);


// return the value in a readable form considering the type
std::string typedValue(int value, int type);


#endif