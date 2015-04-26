#include <iostream>
#include <string>

#include "./Rows.h"
#include "./Indexed.h"
#include "./analyze.h"


int main(int argc, char **argv){
  
  if (argc < 2){
    std::cout << "please provide a file name\n";
    return 1;
  };

  if (argc < 3){
    std::cout << "please provide a file containing queries as parameter 2\n";
    return 1;
  };
  
  if (argc < 4){
    std::cout << "please provide a output filename as parameter 3\n";
    return 1;
  };
  
  
  // parsing
  
  std::string filename = argv[1];
  Rows* r = new Rows(filename);
  
  //displayRows(r); // put in for debugging
  
  Indexed* ix = new Indexed(r);
  
  // end of parsing part
  
  
  
  // analyze and output
  
  std::string queryFilename = argv[2];
  std::string outputFilename = argv[3];
  analyze(ix, queryFilename, outputFilename);
  
  
  
  // cleanup
  
  delete ix;
  
  delete r;
  
};