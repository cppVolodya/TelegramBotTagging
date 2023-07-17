import os

import scripts.data as Data

from scripts.utilities import ValidateValueFromList
from scripts.data.main_data import *


class Console:
    @staticmethod
    def InteractWithUser():
        user_data = Data.User()

        user_data.m_vcpkg_path = Console.GetVcpkgPath()
        user_data.m_build_mode = Console.GetBuildMode()

        if user_data.m_build_mode == Data.User.BuildMode.M_CUSTOM:
            user_data.m_program_architecture = Console.GetProgramArchitecture()

        return user_data

    @staticmethod
    def ValidateVcpkgPath(vcpkg_path):
        if os.path.exists(vcpkg_path):
            file_cmake_of_vcpkg = os.path.join(vcpkg_path, PATH_TO_FILE_VCPKG_CMAKE)
            if os.path.exists(file_cmake_of_vcpkg):
                return True
            else:
                print(f"Invalid path to file {PATH_TO_FILE_VCPKG_CMAKE}.")
                return False
        else:
            print("Directory does not exist.")
            return False

    @staticmethod
    def GetVcpkgPath():
        while True:
            vcpkg_path = input("Enter the path to vcpkg: ")

            if Console.ValidateVcpkgPath(vcpkg_path):
                return vcpkg_path
            else:
                print("Invalid path to vcpkg. Please try again.")

    @staticmethod
    def ValidateBuildMode(build_mode):
        try:
            enum_build_mode = Data.User.BuildMode(build_mode)

            if enum_build_mode in Data.User.BuildMode:
                return True
        except ValueError:
            return False

    @staticmethod
    def GetBuildMode():
        while True:
            print("Choose the build mode:")
            print("[1] - Default (for the current machine architecture)")
            print("[2] - Custom  (you will choose the architecture)")
            print(f"[3] - All     (for both {X32} and {X64} on the current machine architecture)")

            try:
                build_mode = int(input("Enter the build mode number: "))

                if Console.ValidateBuildMode(build_mode):
                    return Data.User.BuildMode(build_mode)
                else:
                    print("Invalid build mode choice. Please try again.")
            except ValueError:
                print("Invalid input. Please enter a valid number.")

    @staticmethod
    def GetProgramArchitecture():
        while True:
            print(f"Choose the program architecture for the build({X32} or {X64}):")
            program_architecture = input("Enter your choice: ")

            if ValidateValueFromList(program_architecture, Data.User.S_PROGRAM_ARCHITECTURES):
                return program_architecture
            else:
                print("Invalid program architecture choice. Please try again.")
