//
// Created by Стёпа on 22.04.2023.
//

#ifndef TTABEL_FILEREADER_H
#define TTABEL_FILEREADER_H
#include <iostream>
#include <fstream>
#include "../Tabel/TScanTable.h"

class FileReader {
private:
    //separation symbols
    std::string sepSym = ",._ \n";
    bool isSep(char symbol);
    virtual void CreateRecord(TScanTable* table,std::string word,int index) = 0;

public:
    void SetSepSym(std::string SepSym){sepSym = SepSym;}
    std::string GetSepSym(){return sepSym;}


    bool ReadeFile(TScanTable* table,std::string filePath);


};


#endif //TTABEL_FILEREADER_H
