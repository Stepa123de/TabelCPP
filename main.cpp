#include "Tabel/TDatValue.h"
#include "Tabel/Record/TWordCounter.h"
#include <iostream>
#include <windows.h>
#include "Tabel/TSortTable.h"
#include "Helps/TWordReader.h"

const std::string path = "C:\\Users\\Стёпа\\Desktop\\TTabel\\test.txt";

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    TSortTable* scan = new TSortTable(1000);


    TWordReader wr;

    wr.ReadeFile(scan,path);

    std::cout << scan->GetDataCount() << std::endl;

    std::string request;
    std::cout << "Book readed" << std::endl;

    TSortTable sort;
    clock_t begin;

    sort.SetSortMethod(SortMeth::BubbleSort);
    begin = clock();
    sort = *scan;
    std::cout << "Efficiency: " << sort.GetEfficiency() << ", Time: "<< (double) (clock() - begin) / CLOCKS_PER_SEC <<", IsSorted: "<<sort.IsSort() << std::endl;

    sort.SetSortMethod(SortMeth::InsertSort);
    begin = clock();
    sort = *scan;
    std::cout << "Efficiency: " << sort.GetEfficiency() << ", Time: "<< (double) (clock() - begin) / CLOCKS_PER_SEC <<", IsSorted: "<<sort.IsSort() << std::endl;

    sort.SetSortMethod(SortMeth::MergeSort);
    begin = clock();
    sort = *scan;
    std::cout << "Efficiency: " << sort.GetEfficiency() << ", Time: "<< (double) (clock() - begin) / CLOCKS_PER_SEC <<", IsSorted: "<<sort.IsSort() << std::endl;

    sort.SetSortMethod(SortMeth::QuickSort);
    begin = clock();
    sort = *scan;
    std::cout << "Efficiency: " << sort.GetEfficiency() << ", Time: "<< (double) (clock() - begin) / CLOCKS_PER_SEC <<", IsSorted: "<<sort.IsSort() << std::endl;

    sort.SetSortMethod(SortMeth::QuickSortInc);
    begin = clock();
    sort = *scan;
    std::cout << "Efficiency: " << sort.GetEfficiency() << ", Time: "<< (double) (clock() - begin) / CLOCKS_PER_SEC <<", IsSorted: "<<sort.IsSort() << std::endl;

    int time;
    while (true) {
        std::cout << "Enter word: ";
        std::cin >> request;
        clock_t begin = clock();
        TWordCounter* twc = (TWordCounter *) scan->FindRecord(request);
        std::cout << "time: " << time << std::endl;
        if (twc == nullptr) {
            std::cout << "CantFindRecord." << std::endl;
        } else {

            std::cout << *twc << std::endl;
            time = (double) (clock() - begin) / CLOCKS_PER_SEC;

        }

    }
    return 0;
}