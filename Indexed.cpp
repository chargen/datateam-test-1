#include "./Indexed.h"
#include <iostream>


Indexed::Indexed(Rows* r){
  this->rows = r;
  
  // create an index for every possible combination of 2 columsn
  // its not the most efficient way in the real world, but the spec says we can take our time at parsing / preparing
  // and the generic analysis must run as fast as possible
  
  ColsByPos::const_iterator it1 = this->rows->headerByPos.begin();
  while (it1 != this->rows->headerByPos.end()){
    
    this->pairIndexes.push_back(new PairIndexPerCol());
    
    // loop through each 2nd column
    ColsByPos::const_iterator it2 = this->rows->headerByPos.begin();
    while (it2 != this->rows->headerByPos.end()){
      
      this->createIndex(it1->pos, it2->pos);
      
      it2++;
    };
    
    it1++;
  };
  
};

// cleanup is rather intense since we use a lot of pointers
void cleanup(PairIndex* idx){
  PairIndex::iterator it = idx->begin();
  while (it != idx->end()){
    delete it->second;
    it++;
  };
};

void cleanup(PairIndexPerCol* idx){
  PairIndexPerCol::iterator it = idx->begin();
  while (it != idx->end()){
    cleanup(it->second);
    delete it->second;
    it++;
  };
};

Indexed::~Indexed(){
  PairIndexesPerCol::iterator it = this->pairIndexes.begin();
  while (it != this->pairIndexes.end()){
    cleanup(*it);
    delete *it;
    it++;
  };
};


// build a specific index
void Indexed::createIndex(size_t col1, size_t col2){
  
  if (col1 == col2){
    return;
  };
  
  std::cout << "creating index: " << col1 << " " << col2 << "\n";
  
  PairIndexPerCol* ent = this->pairIndexes[col1];
  
  PairIndex* index = new PairIndex();
  
  ent->insert(PairIndexPerCol::value_type(col2, index));
  
  // loop through the data and build the index
  rowDataType::const_iterator dataIt = this->rows->rowData.begin();
  
  while (dataIt != this->rows->rowData.end()){
    int value1 = (*dataIt)[col1];
    int value2 = (*dataIt)[col2];
    
    PairIndex::iterator found = index->find(value1);
    if (found == index->end()){
      // no entry for 1st value yet
      
      PairIndexValue* valueEntry = new PairIndexValue();
      valueEntry->insert(PairIndexValue::value_type(value2, 1));
      index->insert(PairIndex::value_type(value1, valueEntry));
      
    }else{
      
      PairIndexValue* valueEntry = found->second;
      PairIndexValue::iterator found2 = valueEntry->find(value2);
      if (found2 == valueEntry->end()){
        // no entry for value 2 yet
        valueEntry->insert(PairIndexValue::value_type(value2, 1));
        
      }else{
        // increase the counter
        found2->second = found2->second + 1;
      };
      
    };
    
    dataIt++;
  };
  
};

// access to a specific index
const PairIndex* Indexed::getIndex(int col1, int col2){

  PairIndexPerCol* perCol = this->pairIndexes[col1];
  PairIndexPerCol::const_iterator idxIt = perCol->find(col2);
  if (idxIt != perCol->end()){
    return idxIt->second;
  };
  
  return 0;

};