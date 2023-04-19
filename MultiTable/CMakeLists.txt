cmake_minimum_required(VERSION 3.25)
project(TTabel)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TTabel
    main.cpp
    TArrayTable.cpp
    TArrayTable.h
    TDatCom.h
    TDatValue.h
    TMarks.cpp
    TMarks.h
    TScanTable.cpp
    TScanTable.h
    TTable.h
    TTabRecord.h
    TWordCounter.cpp
    TWordCounter.h
        v&mfr.txt TSortTable.cpp)
