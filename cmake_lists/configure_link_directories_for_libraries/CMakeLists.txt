macro(ConfigureDefaultBuildForEveryone)
    link_directories(${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib)
endmacro()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    link_directories(${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/lib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    ConfigureDefaultBuildForEveryone()
else()
    ConfigureDefaultBuildForEveryone()
    message(WARNING "Set default library directory: ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib")
endif()
