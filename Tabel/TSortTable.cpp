#include "TSortTable.h"

TSortTable &TSortTable::operator=(const TScanTable &ts) {
    if (pData != nullptr) {
        for (int i = 0; i < this->size; i++) {
            delete pData[i];
        }
        delete[]pData;
        pData = nullptr;
    }
    size = ts.GetSize();
    DataCount = ts.GetDataCount();
    pData = new PTTabRecord[this->size];
    for (int i = 0; i < DataCount; i++) {
        pData[i] = (PTTabRecord) ts.pData[i]->GetCopy();
    }

    SortData();
    curPos = 0;

    return *this;
}

void TSortTable::SortData() {
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
        case SortMeth::QuickSortInc:
            FreeChoice(pData, GetDataCount());
            break;
        default:
            FreeChoice(pData, GetDataCount());
            break;
    }
}

void TSortTable::BubbleSort(PTTabRecord *data, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                Efficiency++;
                std::swap(data[j],data[j + 1]);
            }
        }
    }
}

void TSortTable::InsertSort(PTTabRecord *data, int size) {
    PTTabRecord curElem;
    for (int i = 1; i < size; ++i)
    {
        for (int j = i ; j > 0 && data[j-1] > data[j]; --j)
        {
            std::swap(data[j-1],data[j]);
            Efficiency++;
        }
    }
}

void TSortTable::MergeSort(PTTabRecord *data, int size) {
    PTTabRecord *pBuf = new PTTabRecord[size];
    std::copy(data, data + size, pBuf);

    MergeData(data, pBuf, 0, size - 1);

    delete pBuf;
}

void TSortTable::MergeSorter(PTTabRecord *pData, PTTabRecord *pBuf, int left, int mid, int right) {
    int k = left, i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (pData[i]<= pData[j]) pBuf[k++] = pData[i++];
        else pBuf[k++] = pData[j++];
    }

    Efficiency+=mid-i;
    std::copy(pData + i, pData + mid + 1, pBuf + k);
    Efficiency+=right-left;
    std::copy(pBuf + left, pBuf + right + 1, pData + left);
}

void TSortTable::MergeData(PTTabRecord *pData, PTTabRecord *pBuf, int left, int right) {
    if (left == right) return;

    int mid = left + right >> 1;

    MergeData(pData, pBuf, left, mid);
    MergeData(pData, pBuf, mid + 1, right);

    MergeSorter(pData, pBuf, left, mid, right);
}

void TSortTable::FreeChoice(PTTabRecord *data, int size) {
    std::sort(data, data + size);
}

void TSortTable::QuickSort(PTTabRecord *data, int size) {
    QuickSplit(data, 0, size - 1);
}

void TSortTable::QuickSplit(PTTabRecord *data, int minIndex, int maxIndex) {
    int leftIndex = minIndex;
    int rightIndex = maxIndex;
    PTDatValue pivot = data[(minIndex+maxIndex)>>1];
    while (minIndex < maxIndex)
    {
        while (data[minIndex] < pivot) minIndex++;
        while (data[maxIndex] > pivot) maxIndex--;

        if(minIndex < maxIndex)
        {
            Efficiency++;
            std::swap(data[minIndex],data[maxIndex]);
            minIndex++;
            maxIndex--;
        }
    }

    if (rightIndex - leftIndex < 2) return;

    QuickSplit(data,leftIndex,maxIndex);
    QuickSplit(data,minIndex,rightIndex);
}

PTDatValue TSortTable::FindRecord(TKey key) {
    int first = 0, last = DataCount - 1, mid;
    Efficiency = 0;
    SetRetCode(TAB_OK);
    while (first < last) {
        Efficiency++;
        mid = (first + last)>>1;
        if (pData[mid]->GetKey() == key) {
            first = mid + 1;
            last = mid;
        }
        else if (pData[mid]->GetKey() > key)
            last = mid - 1;
        else
            first = mid + 1;
    }
    if (last < 0 || pData[last]->GetKey() < key) { // Ìîæåò ëè áûòü mid < 0
        last++;
    }
    curPos = last;
    if (last < DataCount && (pData[last]->GetKey() == key)) {
        SetRetCode(TAB_OK);
        return pData[last]->GetValue();
    }
    SetRetCode(TAB_NO_RECORD);
    return nullptr;
}

bool TSortTable::InsertRecord(TKey key, PTDatValue value) {
    if (isFull()) {
        SetRetCode(TAB_FULL);
    }
    else {
        PTDatValue tmp = FindRecord(key);
        if (RetCode == TAB_OK) {
            SetRetCode(TAB_REC_DOUBLE);
        }
        else {
            RetCode = TAB_OK;
            for (int i = DataCount; i > curPos; i--){
                pData[i] = pData[i - 1];
            }
            pData[curPos] = new TTabRecord(key,value);
            DataCount++;
        }
    }
}

void TSortTable::DeleteRecord(TKey key) {
    FindRecord(key);
    if (RetCode == TAB_OK) {
        SetRetCode(TAB_OK);
        for (int i = curPos; i < DataCount - 1; i++) {
            pData[i] = pData[i + 1];
        }

        pData[--DataCount] = nullptr;
    } //проблема с утечкой памяти

}

bool TSortTable::IsSort()
{
    for (int i = 0 ; i < DataCount - 1; ++i) if(pData[i] > pData[i+1]) return false;
    return true;
}
