#pragma once
#include "Tabel/TDatValue.h"

enum class wordType 
{
	WORD,
	NUM,
	SIM,
};

enum class language
{
	RUSSIAN,
	FRENCH,
	NONE,
};

class TWordCounter : public TDatValue
{
private:
	wordType _wt;
	language _l;
	int _data[3] = {0,-1,-1};

	std::string languageConverter() const
	{
		switch (_l)
		{
		case language::RUSSIAN:
			return "russian";
			break;
		case language::FRENCH:
			return "french";
			break;
		case language::NONE:
			return "none";
			break;
		}
	}

	std::string wordTyepeConverter() const
	{
		switch(_wt)
		{
		case wordType::WORD:
			return "word";
			break;
		case wordType::NUM:
			return "num";
			break;
		case wordType::SIM:
			return "sim";
			break;
		}
	}
public:
	TWordCounter(int count, int first, int last, wordType wt, language l): _wt(wt), _l(l)
	{
		_data[0] = count;
		_data[1] = first;
		_data[2] = last;
	}

	void CountPlus() 
	{ 
		_data[0]++;
	};

	void last(int last) 
	{
		_data[2] = last;
	}

	TDatValue* GetCopy() override
	{
		return new TWordCounter(_data[0], _data[1], _data[2], _wt, _l);
	}

	void Print(std::ostream& os) const override 
	{
		os << "Count: " << _data[0] << ", ";
		os << "First: " << _data[1] << ", ";
		os << "Last: " << _data[2] << ", ";
		os << "WordType: " << wordTyepeConverter() << ", ";
		os << "Language: " << languageConverter() << '\t';

	}
};
