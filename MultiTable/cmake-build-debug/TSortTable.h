#pragma once
#include "TScanTable.h"

enum SortMeth{
	BubbleSort,
	QuickSort,
	MergeSort,
	InsertSort,
	FreeChoice // на выбор
};

class TSortTable : public TScanTable
{
protected:
	SortMeth _sortMethod;
	void SortData();
	void BubbleSort(PTTabRecord* data, int size);
	void InsertSort(PTTabRecord* data, int size);
	void MergeSort(PTTabRecord* data, int size);
	void MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuf, int size); //Нужны для сортировки слиянием
	void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuf, int n1, int n2); //
	void FreeChoice(PTTabRecord* data, int size);
	void QuickSort(PTTabRecord* data, int size);
	void QuickSplit(PTTabRecord* data, int size, int& pivot); //pivot - опорный элемент
public:
	TSortTable(int size = 50) : TScanTable(size) {};
	TSortTable(const TScanTable& st) {
		*this = st;
	}
	TSortTable& operator=(const TScanTable& ts);
	SortMeth GetSortMethod() {
		return _sortMethod;
	}
	void SetSortMethod(SortMeth sm) {
		_sortMethod = sm;
	}
	virtual PTDatValue FindRecord(TKey key) override;
	virtual bool InsertRecord(TKey key, PTDatValue value) override;
	virtual void DeleteRecord(TKey key) override;

};

