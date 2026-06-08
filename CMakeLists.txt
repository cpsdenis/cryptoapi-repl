cmake_minimum_required(VERSION 3.15)
project(capirepl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_path(CRYPTOPRO_SDK_INCLUDE_DIR
    NAMES WinCryptEx.h
    PATHS
        "C:/include/cpcsp"
    DOC "Path to the CryptoPro CSP SDK include directory"
)

add_subdirectory(src)
