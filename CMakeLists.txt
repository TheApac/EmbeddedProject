cmake_minimum_required(VERSION 3.8)
project(untitled6)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c sources/src/readCountryFromPlaneCode.c sources/include/readCountryFromPlaneCode.h sources/src/raiseError.c sources/include/raiseError.h sources/src/readTypePlaneFromValue.c sources/include/readTypePlaneFromValue.h sources/src/readFailureFromValue.c sources/include/readFailureFromValue.h sources/src/readComponentFromValue.c sources/include/readComponentFromValue.h sources/src/printInLogFile.c sources/include/printInLogFile.h sources/src/getFormattedDate.c sources/include/getFormattedDate.h sources/src/plane.c sources/include/plane.h sources/src/failure.c sources/include/failure.h tests/testReads/testReadComponentFromValue.c sources/src/hex2dec.c sources/include/hex2dec.h)
add_executable(untitled6 ${SOURCE_FILES})