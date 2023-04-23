////
//// Created by Стёпа on 22.04.2023.
////

#ifndef TTABEL_TWORDREADER_H
#define TTABEL_TWORDREADER_H
#include "FileReader.h"
#include "../Tabel/Record/TWordCounter.h"

class TWordReader: public FileReader {
private:
    void CreateRecord(TScanTable* table,std::string word,int index) override;
};


#endif //TTABEL_TWORDREADER_H
