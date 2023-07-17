import os

from scripts.data.main_data import *


class CmakeBuilder:
    def __init__(self, system_data, user_data, program_architecture):
        self.m_program_architecture = program_architecture
        self.m_system_data          = system_data
        self.m_user_data            = user_data

        self.m_generator_of_build_files  = None
        self.m_program_architecture_flag = None
        self.m_option_config             = None

    def Start(self):
        self.Configure()
        self.GenerateBuildFiles()
        self.Build()

    def Configure(self):
        if self.m_system_data.m_os_type == LINUX:
            self.m_generator_of_build_files  = GENERATOR_OF_BUILD_FILES_FOR_LINUX
            self.m_program_architecture_flag = ""
            self.m_option_config             = ""
        elif self.m_system_data.m_os_type == WINDOWS:
            self.m_generator_of_build_files  = GENERATOR_OF_BUILD_FILES_FOR_WINDOWS
            self.m_program_architecture_flag = "-A Win32" if self.m_program_architecture == X32 else f"-A {X64}"
            self.m_option_config             = f"--config {CMAKE_BUILD_TYPE}"

    def GenerateBuildFiles(self):
        command = \
            (
                f'cmake . '
                f'-DCMAKE_BUILD_TYPE={CMAKE_BUILD_TYPE} '
                f'-B {BUILD_DIR}/{self.m_system_data.m_os_type}/{CMAKE_BUILD_TYPE}/{self.m_program_architecture}/ '
                f'-G "{self.m_generator_of_build_files}" '
                f'-DVCPKG_PATH="{self.m_user_data.m_vcpkg_path}" '
                f'-DOPERATING_SYSTEM_ARCHITECTURE="{self.m_program_architecture}" '
                f'{self.m_program_architecture_flag}'
            )

        exit_code = os.system(command)
        if exit_code != 0:
            raise OSError("Error generating build files.")

    def Build(self):
        command = \
            (
                f'cmake '
                f'--build {BUILD_DIR}/{self.m_system_data.m_os_type}/{CMAKE_BUILD_TYPE}/'
                f'{self.m_program_architecture}/ '
                f'-j{self.m_system_data.m_number_of_threads} '
                f'{self.m_option_config}'
            )

        exit_code = os.system(command)
        if exit_code != 0:
            raise OSError("Error building project.")
