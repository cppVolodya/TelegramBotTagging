if(OPERATING_SYSTEM_ARCHITECTURE STREQUAL "x64")
    set(CMAKE_GENERATOR_PLATFORM x64)
    set(VCPKG_TARGET_TRIPLET "x64-windows-static")

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(LINKER_OPTIONS "/LTCG")
    endif()

    set(LIBRARY_SSL    "${PROJECT_SOURCE_DIR}/libraries/openssl_for_windows/x64/lib/libssl.lib")
    set(LIBRARY_CRYPTO "${PROJECT_SOURCE_DIR}/libraries/openssl_for_windows/x64/lib/libcrypto.lib")
elseif(OPERATING_SYSTEM_ARCHITECTURE STREQUAL "x32")
    set(CMAKE_GENERATOR_PLATFORM win32)
    set(VCPKG_TARGET_TRIPLET "x86-windows-static")

    set(LIBRARY_SSL    "${PROJECT_SOURCE_DIR}/libraries/openssl_for_windows/x32/lib/libssl.lib")
    set(LIBRARY_CRYPTO "${PROJECT_SOURCE_DIR}/libraries/openssl_for_windows/x32/lib/libcrypto.lib")
endif()
