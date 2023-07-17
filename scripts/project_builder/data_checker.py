import os

from scripts.data.main_data import *


class DataChecker:
    def __init__(self, system_data, user_data):
        self.m_system_data = system_data
        self.m_user_data   = user_data

    def Start(self, program_architecture):
        DataChecker.CheckLibrariesAvailability()
        self.CheckVcpkgTripletAvailability(program_architecture)

    @staticmethod
    def CheckLibrariesAvailability():
        DataChecker.CheckLibrariesOfBsThreadPooL()
        DataChecker.CheckLibrariesOfOpenSsl()

    @staticmethod
    def CheckLibrariesOfBsThreadPooL():
        if not os.path.exists(PATH_TO_FILE_BS_THREAD_POOL_LIGHT_HPP):
            raise OSError("File does not exist: " + PATH_TO_FILE_BS_THREAD_POOL_LIGHT_HPP)
        if not os.path.exists(PATH_TO_FILE_BS_THREAD_POOL_HPP):
            raise OSError("File does not exist: " + PATH_TO_FILE_BS_THREAD_POOL_HPP)

    @staticmethod
    def CheckLibrariesOfOpenSsl():
        DataChecker.CheckLibrariesOfOpenSslX32()
        DataChecker.CheckLibrariesOfOpenSslX64()

    @staticmethod
    def CheckLibrariesOfOpenSslX32():
        DataChecker.CheckLibrariesOfOpenSslLibX32()
        DataChecker.CheckLibrariesOfOpenSslDllX32()

    @staticmethod
    def CheckLibrariesOfOpenSslLibX32():
        if not os.path.exists(PATH_TO_FILE_LIBSSL_LIB_FOR_WINDOWS_X32):
            raise OSError("File does not exist: " + PATH_TO_FILE_LIBSSL_LIB_FOR_WINDOWS_X32)
        if not os.path.exists(PATH_TO_FILE_LIBCRYPTO_LIB_FOR_WINDOWS_X32):
            raise (OSError("File does not exist: " + PATH_TO_FILE_LIBCRYPTO_LIB_FOR_WINDOWS_X32))

    @staticmethod
    def CheckLibrariesOfOpenSslDllX32():
        if not os.path.exists(PATH_TO_FILE_LIBSSL3_DLL_FOR_WINDOWS_X32):
            raise OSError("File does not exist: " + PATH_TO_FILE_LIBSSL3_DLL_FOR_WINDOWS_X32)
        if not os.path.exists(PATH_TO_FILE_LIBCRYPTO3_DLL_FOR_WINDOWS_X32):
            raise OSError("File does not exist: " + PATH_TO_FILE_LIBCRYPTO3_DLL_FOR_WINDOWS_X32)

    @staticmethod
    def CheckLibrariesOfOpenSslX64():
        DataChecker.CheckLibrariesOfOpenSslLibX64()
        DataChecker.CheckLibrariesOfOpenSslDllX64()

    @staticmethod
    def CheckLibrariesOfOpenSslLibX64():
        if not os.path.exists(PATH_TO_FILE_LIBSSL_LIB_FOR_WINDOWS_X64):
            raise OSError("File does not exist: " + PATH_TO_FILE_LIBSSL_LIB_FOR_WINDOWS_X64)
        if not os.path.exists(PATH_TO_FILE_LIBCRYPTO_LIB_FOR_WINDOWS_X64):
            raise OSError("File does not exist: " + PATH_TO_FILE_LIBCRYPTO_LIB_FOR_WINDOWS_X64)

    @staticmethod
    def CheckLibrariesOfOpenSslDllX64():
        if not os.path.exists(PATH_TO_FILE_LIBSSL3_DLL_FOR_WINDOWS_X64):
            raise OSError("File does not exist: " + PATH_TO_FILE_LIBSSL3_DLL_FOR_WINDOWS_X64)
        if not os.path.exists(PATH_TO_FILE_LIBCRYPTO3_DLL_FOR_WINDOWS_X64):
            raise OSError("File does not exist: " + PATH_TO_FILE_LIBCRYPTO3_DLL_FOR_WINDOWS_X64)

    def CheckVcpkgTripletAvailability(self, program_architecture):
        name_of_triplet = None
        if self.m_system_data.m_os_type == LINUX:
            name_of_triplet = NAME_OF_TRIPLET_FOR_LINUX_X32 if program_architecture == X32 else NAME_OF_TRIPLET_FOR_LINUX_X64
        elif self.m_system_data.m_os_type == WINDOWS:
            name_of_triplet = NAME_OF_TRIPLET_FOR_WINDOWS_X32 if program_architecture == X32 else NAME_OF_TRIPLET_FOR_WINDOWS_X64

        vcpkg_triplet_dir_path = f"{self.m_user_data.m_vcpkg_path}/installed/{name_of_triplet}/"
        if os.path.exists(vcpkg_triplet_dir_path):
            return True
        else:
            print(f"Vcpkg triplet for {program_architecture} does not exist: {vcpkg_triplet_dir_path}")
            print(f"Download the triplet for the current architecture and try again: 'vcpkg install tgbot-cpp sqlitecpp --triplet=\"{name_of_triplet}\"'")
            raise OSError("Vcpkg triplet does not exist.")
