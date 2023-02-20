if(NOT DEFINED VCPKG_PATH)
    message(FATAL_ERROR "VCPKG_PATH is not defined")
endif()

set(VCPKG_INSTALLED_DIR ${VCPKG_PATH}/installed)
