#pragma once
#include "TScanTable.h"
#include <algorithm>

enum SortMeth{
	BubbleSort,
	QuickSort,
	MergeSort,
	InsertSort,
    QuickSortInc,
};

class TSortTable : public TScanTable
{
protected:
	SortMeth _sortMethod;
    void BubbleSort(PTTabRecord* data, int size);
	void InsertSort(PTTabRecord* data, int size);
	void MergeSort(PTTabRecord* data, int size);
	void MergeSorter(PTTabRecord* pData, PTTabRecord* pBuf, int left, int mid, int right); //Нужны для сортировки слиянием
	void MergeData(PTTabRecord* pData, PTTabRecord* pBuf, int left, int right); //
	void FreeChoice(PTTabRecord* data, int size);
	void QuickSort(PTTabRecord* data, int size);
	void QuickSplit(PTTabRecord* data, int minIndex, int maxIndex); //pivot - опорный элемент
public:
    void SortData();
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
    bool InsertRecord(TKey key, PTDatValue value) override;
	void DeleteRecord(TKey key) override;

};

