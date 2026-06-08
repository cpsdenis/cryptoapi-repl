add_executable(capirepl main.cpp)

if(NOT CRYPTOPRO_SDK_INCLUDE_DIR)
    message(FATAL_ERROR "CryptoPro CSP SDK not found! Please specify the path manually using -DCRYPTOPRO_SDK_INCLUDE_DIR=...")
endif()

target_include_directories(capirepl PRIVATE ${CRYPTOPRO_SDK_INCLUDE_DIR})

if(WIN32)
    target_link_libraries(capirepl PRIVATE crypt32)
else()
    message(FATAL_ERROR "This example is intended for Windows only.")
endif()
