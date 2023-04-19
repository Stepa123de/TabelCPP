#include "TDatValue.h"
#include "TScanTable.h"
#include "TWordCounter.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "TSortTable.h"

#define FFR 'a'
#define LFR 'z'
#define BFFR 'A'
#define BLFR 'Z'

const std::string path = "C:\\Users\\Стёпа\\Desktop\\TTabel\\v&mru.txt";

bool isWord(char c)
{
    return c == '.' || c >= ',' && c <= '\n' || c >= ' ' && c <= '  ';
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    TSortTable scan = TScanTable(100);

    TWordCounter* twc;


    std::ifstream file(path);
    if (file.is_open())
    {
        char c;
        std::string word = "";
        wordType wt;
        language l;
        int simCount = 0;
        while (file.get(c))
        {
            simCount++;
            if (!isWord(c))
            {
                word += c;
            }
            else
            {
                twc = (TWordCounter*)scan.FindRecord(word);
                if(twc==nullptr)
                {
                    if (word[0] >= '0' && word[0] <= '9')
                    {
                        wt = wordType::NUM;
                        l = language::NONE;
                    }
                    else if (isWord(word[0]))
                    {
                        wt = wordType::WORD;
                        if (word[0] >= FFR && word[0] <= LFR || word[0] >= BFFR && word[0] <= BLFR) l = language::FRENCH;
                        else l = language::RUSSIAN;
                    }
                    else
                    {
                        l = language::NONE;
                        wt = wordType::SIM;
                    }

                    scan.InsertRecord(word, new TWordCounter(1, simCount - 1, simCount - 1, wt, l));
                }
                else
                {
                    twc->CountPlus();
                    twc->last(simCount - 1);
                }
                word = c;
                twc = (TWordCounter*)scan.FindRecord(word);
                if(twc == nullptr)
                {
                    scan.InsertRecord(word, new TWordCounter(1, simCount - 1, simCount - 1, wordType::SIM, language::NONE));
                }
                else
                {
                    twc->CountPlus();
                    twc->last(simCount - 1);
                }
                word = "";
            }

        }
        file.close();

    }


    std::string request;
    std::cout << "Book readed"<< std::endl;

    scan.SetSortMethod(SortMeth::BubbleSort);
    scan.SortData();
    scan.SetSortMethod(SortMeth::InsertSort);
    scan.SortData();
    scan.SetSortMethod(SortMeth::MergeSort);
    scan.SortData();
    scan.SetSortMethod(SortMeth::QuickSort);
    //scan.SortData();
    scan.SetSortMethod(SortMeth::QuickSortInc);
    scan.SortData();

    while (true)
    {
        std::cout << "Enter word: ";
        std::cin >> request;
        clock_t begin = clock();
        twc = (TWordCounter*)scan.FindRecord(request);
        std::cout << "time: " << time << std::endl;
        if (twc == nullptr)
        {
            std::cout << "CantFindRecord." << std::endl;
        }
        else
        {

            std::cout << *twc << std::endl;
            int time = (double)(clock() - begin) / CLOCKS_PER_SEC;

        }

    }
    return 0;
}