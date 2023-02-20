# --------------------------------------------------------------------------- #
# Basic settings
cmake_minimum_required(VERSION 3.22.1)
project(telegram_bot_tagging)
# --------------------------------------------------------------------------- #


# --------------------------------------------------------------------------- #
# Loading additional settings
include(cmake_lists/configure_cpp/CMakeLists.txt)
include(cmake_lists/configure_vcpkg/CMakeLists.txt)
include(cmake_lists/configure_bshoshany_thread_pool/CMakeLists.txt)
include(cmake_lists/operating_system_architecture_detection/CMakeLists.txt)
include(cmake_lists/configure_os/CMakeLists.txt)
include(cmake_lists/include_library_directories/CMakeLists.txt)
include(cmake_lists/configure_link_directories_for_libraries/CMakeLists.txt)
include(cmake_lists/include_custom_directories/CMakeLists.txt)
include(cmake_lists/collect_program_files/CMakeLists.txt)
include(cmake_lists/configure_executable_program/CMakeLists.txt)
# --------------------------------------------------------------------------- #
