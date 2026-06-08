add_executable(capirepl main.cpp)

if(NOT CRYPTOPRO_SDK_INCLUDE_DIR)
    message(FATAL_ERROR "CryptoPro SDK not found! Please specify the path manually using -DCRYPTOPRO_SDK_INCLUDE_DIR=...")
endif()

target_include_directories(capirepl PRIVATE 
    ${CRYPTOPRO_SDK_INCLUDE_DIR} 
    ${CRYPTOPRO_SDK_INCLUDE_DIR}/cpcsp
)

if(WIN32)
    target_link_libraries(capirepl PRIVATE crypt32)
else()
    find_library(CAPILITE_LIB10 NAMES capi10 PATHS "/opt/cprocsp/lib/amd64" "/opt/cprocsp/lib")
    find_library(CAPILITE_LIB20 NAMES capi20 PATHS "/opt/cprocsp/lib/amd64" "/opt/cprocsp/lib")

    if(NOT CAPILITE_LIB10)
        message(FATAL_ERROR "CryptoPro CAPI-Lite libraries not found! Ensure CSP is installed.")
    endif()

    target_link_libraries(capirepl PRIVATE ${CAPILITE_LIB10} ${CAPILITE_LIB20})

    target_compile_definitions(capirepl PRIVATE 
        UNIX
        SIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P}
    )
endif()