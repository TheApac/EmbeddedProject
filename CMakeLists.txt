cmake_minimum_required(VERSION 3.8)
project(untitled6)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c sources/readCountryFromPlaneCode.c sources/readCountryFromPlaneCode.h sources/readTypePlaneFromValue.c sources/readTypePlaneFromValue.h sources/readFailureFromValue.c sources/readFailureFromValue.h sources/readComponentFromValue.c sources/readComponentFromValue.h sources/getFormattedDate.c sources/getFormattedDate.h sources/plane.h sources/failure.c sources/failure.h tests/testReadComponentFromValue.c sources/hex2dec.c sources/hex2dec.h)
add_executable(untitled6 ${SOURCE_FILES})