#include "TDatValue.h"
#include "TTabRecord.h"
#include "TArrayTable.h"
#include "TScanTable.h"
#include "TMarks.h"
#include "TWordCounter.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#define FRU 'а'
#define LRU 'я'
#define FFR 'a'
#define LFR 'z'
#define BFRU 'А'
#define BLRU 'Я'
#define BFFR 'A'
#define BLFR 'Z'

const std::string path = "v&mru.txt";

bool isWord(char c)
{
	return c == '-' || c == '’' || c >= '0' && c <= '9' || c >= FRU && c <= LRU || c >= BFRU && c <= BLRU || c >= FFR && c <= LFR || c >= BFFR && c <= BLFR;
}

int main() {
	TScanTable scan = TScanTable(100000);

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
			if (isWord(c))
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
						if (word[0] >= FRU && word[0] <= LRU || word[0] >= BFRU && word[0] <= BLRU) l = language::RUSSIAN;
						else l = language::FRENCH;
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
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::string request;
	std::cout << "Efficiency: " << scan.GetEfficiency() << std::endl;
	while (true)
	{
		std::cout << "Enter word: ";
		std::cin >> request;
		clock_t begin = clock();
		twc = (TWordCounter*)scan.FindRecord(request);
		std::cout << "time: " << time << std::endl;
		if (twc == nullptr)
		{
			std::cout << "Нету такого слова." << std::endl;
		}
		else 
		{
			
			std::cout << *twc << std::endl;
			int time = (double)(clock() - begin) / CLOCKS_PER_SEC;
			
		}
		
	}
	return 0;
}