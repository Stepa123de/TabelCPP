#include "TScanTable.h"

PTDatValue TScanTable::FindRecord(TKey key)
{
    int i;
    SetRetCode(TAB_OK);
    for (i = 0; i < DataCount; i++)
    {
        if (pData[i]->_key == key)
        {
            Efficiency += i + 1;
            return pData[i]->_value;
        }
    }
    Efficiency += i + 1;

    SetRetCode(TAB_NO_RECORD);
    return nullptr;
}

bool TScanTable::InsertRecord(TKey key, PTDatValue value)
{
    if (this->isFull())
    {
        SetRetCode(TAB_FULL);
        return false;
    }
    //std::cout << key << " ";
    pData[DataCount] = new TTabRecord(key, value);
    DataCount++;
    SetRetCode(TAB_OK);
    return true;
}

void TScanTable::DeleteRecord(TKey key)
{
    for (int i = 0; i < size; ++i) {
        std::cout << pData[i];
    }
    PTDatValue t =  this->FindRecord(key);
    if (t == nullptr)
        SetRetCode(TAB_NO_RECORD);
    else
    {
        SetRetCode(TAB_OK);
        pData[curPos] = pData[DataCount - 1];
        pData[--DataCount] = nullptr;
    }
}
