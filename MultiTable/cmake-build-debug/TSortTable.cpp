#include "TSortTable.h"

TSortTable& TSortTable::operator=(const TScanTable& ts)
{
    if (pData != nullptr) {
        for (int i = 0; i < DataCount; i++){
            delete pData[i];
        }
        delete []pData;
        pData = nullptr;
    }
    size = ts.GetSize();
    DataCount = ts.GetDataCount();
    pData = new PTTabRecord[this->size];
    for (int i = 0; i < DataCount; i++) {
        pData[i] = (PTTabRecord)ts.pData[i]->GetCopy();
    }

    SortData();
    curPos = 0;

    return *this;
}

void TSortTable::SortData()
{
    Efficiency = 0;
    switch (_sortMethod) {
        case SortMeth::BubbleSort:
            BubbleSort(pData, GetDataCount());
            break;
        case SortMeth::QuickSort:
            QuickSort(pData, GetDataCount());
            break;
        case SortMeth::MergeSort:
            MergeSort(pData, GetDataCount());
            break;
        case SortMeth::InsertSort:
            InsertSort(pData, GetDataCount());
            break;
        default:
            FreeChoice(pData, GetDataCount());
            break;
    }
}

void TSortTable::BubbleSort(PTTabRecord* data, int size)
{
}

void TSortTable::InsertSort(PTTabRecord* data, int size)
{
    PTTabRecord curElem;
    Efficiency = DataCount;
    for (int i = 1,j; i < DataCount; i++) {
        curElem = data[i];
        for (j = i - 1; j > -1; j--) {
            if (data[j]->GetKey() > curElem->GetKey()) {
                data[j + 1] = data[j];
                Efficiency++;
            }
            else {
                break;
            }
        
        }
        data[j + 1] = curElem;
    }
}

void TSortTable::MergeSort(PTTabRecord* data, int size)
{
}

void TSortTable::FreeChoice(PTTabRecord* data, int size)
{
}

void TSortTable::QuickSort(PTTabRecord* data, int size)
{
}
