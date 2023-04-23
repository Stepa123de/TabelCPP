////
//// Created by Стёпа on 22.04.2023.
////

#include "TWordReader.h"

void TWordReader::CreateRecord(TScanTable* table, std::string word, int index)
{
    wordType wt;
    language l;
    TWordCounter* twc = (TWordCounter *) table->FindRecord(word);
    if (twc == nullptr) {
        if (word[0] >= '0' && word[0] <= '9') {
            wt = wordType::NUM;
            l =language::NONE;
        } else if (word[0]!='.' || word[0]!=',' || word[0]!=' ' || word[0]!= '\n') {
            wt = wordType::WORD;
            if (word[0] >= 'a' && word[0] <= 'z' || word[0] >= 'A' && word[0] <= 'Z') l = language::FRENCH;
            else l = language::RUSSIAN;
        } else {
            l = language::NONE;
            wt = wordType::SIM;
        }

        table->InsertRecord(word, new TWordCounter(1, index, index, wt, l));

    } else {
        twc->CountPlus();
        twc->last(index);
    }
}
