cmake_minimum_required(VERSION 3.15)
project(capirepl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    find_path(CRYPTOPRO_SDK_INCLUDE_DIR
        NAMES cpcsp/WinCryptEx.h
        PATHS "C:/include"
        NO_DEFAULT_PATH
    )
else()
    find_path(CRYPTOPRO_SDK_INCLUDE_DIR
        NAMES cpcsp/WinCryptEx.h cpcsp/CSP_WinCrypt.h
        PATHS "/opt/cprocsp/include"
        NO_DEFAULT_PATH 
    )
endif()

message(STATUS "CRYPTOPRO_SDK_INCLUDE_DIR value: ${CRYPTOPRO_SDK_INCLUDE_DIR}")

add_subdirectory(src)