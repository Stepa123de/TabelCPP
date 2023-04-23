//
// Created by Стёпа on 22.04.2023.
//

#include "FileReader.h"

bool FileReader::ReadeFile(TScanTable* table, std::string filePath)
{
    std::ifstream file(filePath);
    
    if(!file.is_open()) return false;

    int symIndex = -1;
    char symbol;
    std::string word;

    while (file.get(symbol))
    {
        symIndex++;
        if(isSep(symbol))
        {
            CreateRecord(table,word,symIndex-word.size());
            word="";
        }
        else
        {
            word+=symbol;
        }
    }


    return true;
}

bool FileReader::isSep(char symbol) {
    for (int i = 0; i < sepSym.size(); ++i)
    {
        if(symbol == sepSym[i]) return true;
    }
    return false;
}

