# --------------------------------------------------------------- #
# Options for CMake
CMAKE_BUILD_TYPE = "Release"
GENERATOR_OF_BUILD_FILES_FOR_LINUX = "Unix Makefiles"
GENERATOR_OF_BUILD_FILES_FOR_WINDOWS = "Visual Studio 17 2022"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# OS names
WINDOWS = "windows"
LINUX = "linux"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# OS architecture names
X32 = "x32"
X64 = "x64"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# Desktop(Shortcut) file names
DESKTOP_FILE_NAME_FOR_LINUX_X32 = f"Telegram Bot Tagging({X32}).desktop"
DESKTOP_FILE_NAME_FOR_LINUX_X64 = f"Telegram Bot Tagging({X64}).desktop"

SHORTCUT_FILE_NAME_FOR_WINDOWS_X32 = f"Telegram Bot Tagging({X32}).lnk"
SHORTCUT_FILE_NAME_FOR_WINDOWS_X64 = f"Telegram Bot Tagging({X64}).lnk"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# Path to directory of OpenSSL for Windows
PATH_TO_LIBRARY_OF_OPENSSL_FOR_WINDOWS = "libraries/openssl_for_windows"

PATH_TO_LIBRARY_LIB_OF_OPENSSL_FOR_WINDOWS_X32 = f"{PATH_TO_LIBRARY_OF_OPENSSL_FOR_WINDOWS}/x32/lib"
PATH_TO_LIBRARY_BIN_OF_OPENSSL_FOR_WINDOWS_X32 = f"{PATH_TO_LIBRARY_OF_OPENSSL_FOR_WINDOWS}/x32/bin"

PATH_TO_LIBRARY_LIB_OF_OPENSSL_FOR_WINDOWS_X64 = f"{PATH_TO_LIBRARY_OF_OPENSSL_FOR_WINDOWS}/x64/lib"
PATH_TO_LIBRARY_BIN_OF_OPENSSL_FOR_WINDOWS_X64 = f"{PATH_TO_LIBRARY_OF_OPENSSL_FOR_WINDOWS}/x64/bin"
# --------------------------------------------------------------- #

# --------------------------------------------------------------- #
# Path to libraries(lib) of OpenSSL for Windows
PATH_TO_FILE_LIBCRYPTO_LIB_FOR_WINDOWS_X32 = f"{PATH_TO_LIBRARY_LIB_OF_OPENSSL_FOR_WINDOWS_X32}/libcrypto.lib"
PATH_TO_FILE_LIBSSL_LIB_FOR_WINDOWS_X32    = f"{PATH_TO_LIBRARY_LIB_OF_OPENSSL_FOR_WINDOWS_X32}/libssl.lib"

PATH_TO_FILE_LIBCRYPTO_LIB_FOR_WINDOWS_X64 = f"{PATH_TO_LIBRARY_LIB_OF_OPENSSL_FOR_WINDOWS_X64}/libcrypto.lib"
PATH_TO_FILE_LIBSSL_LIB_FOR_WINDOWS_X64    = f"{PATH_TO_LIBRARY_LIB_OF_OPENSSL_FOR_WINDOWS_X64}/libssl.lib"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# Path to libraries(dll) of OpenSSL for Windows
PATH_TO_FILE_LIBSSL3_DLL_FOR_WINDOWS_X32    = f"{PATH_TO_LIBRARY_BIN_OF_OPENSSL_FOR_WINDOWS_X32}/libssl-3.dll"
PATH_TO_FILE_LIBCRYPTO3_DLL_FOR_WINDOWS_X32 = f"{PATH_TO_LIBRARY_BIN_OF_OPENSSL_FOR_WINDOWS_X32}/libcrypto-3.dll"

PATH_TO_FILE_LIBSSL3_DLL_FOR_WINDOWS_X64    = f"{PATH_TO_LIBRARY_BIN_OF_OPENSSL_FOR_WINDOWS_X64}/libssl-3-x64.dll"
PATH_TO_FILE_LIBCRYPTO3_DLL_FOR_WINDOWS_X64 = f"{PATH_TO_LIBRARY_BIN_OF_OPENSSL_FOR_WINDOWS_X64}/libcrypto-3-x64.dll"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# Path to directory of BS thread pool
PATH_TO_LIBRARY_OF_BS_THREAD_POOL = "libraries/bshoshany_thread_pool"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# Path to files of BS thread pool
PATH_TO_FILE_BS_THREAD_POOL_LIGHT_HPP = f"{PATH_TO_LIBRARY_OF_BS_THREAD_POOL}/include/BS_thread_pool_light.hpp"
PATH_TO_FILE_BS_THREAD_POOL_HPP       = f"{PATH_TO_LIBRARY_OF_BS_THREAD_POOL}/include/BS_thread_pool.hpp"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# Path to another files or directories
PATH_TO_FILE_VCPKG_CMAKE = "scripts/buildsystems/vcpkg.cmake"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# Triplet names
NAME_OF_TRIPLET_FOR_LINUX_X32 = "x86-linux"
NAME_OF_TRIPLET_FOR_LINUX_X64 = "x64-linux"

NAME_OF_TRIPLET_FOR_WINDOWS_X32 = "x86-windows-static"
NAME_OF_TRIPLET_FOR_WINDOWS_X64 = "x64-windows-static"
# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# Directory names
BUILD_DIR = "build"
INSTALLED_PROGRAM_DIR = "program"

IMAGE_DIR = "images"
CONFIG_DIR = "config"
LOG_FILES_DIR = "log_files"

DATABASE_DIR = "database"

DESKTOP_DIR = "Desktop"

# --------------------------------------------------------------- #


# --------------------------------------------------------------- #
# File names
DATABASE_FILE_PATH = "database/telegram_bot_tagging.db"

EXUCUTABLE_FILE_NAME_FOR_LINUX = "telegram_bot_tagging"
EXUCUTABLE_FILE_NAME_FOR_WINDOWS = "telegram_bot_tagging.exe"

IMAGE_FILE_NAME_FOR_LINUX = "linux_icon_for_program.png"
IMAGE_FILE_NAME_FOR_WINDOWS = "windows_icon_for_program.ico"

LOCAL_SHARE_APPLICATIONS_DIR_PATH_FOR_LINUX = ".local/share/applications"
# --------------------------------------------------------------- #
