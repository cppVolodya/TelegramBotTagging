import os
import shutil

import scripts.project_builder.program_installer as ProgramInstaller

from scripts.data.main_data import *


class MainProgramInstaller:
    def __init__(self, system_info):
        self.m_system_info = system_info

    def Start(self, program_architecture):
        program_dir = self.GetProgramDirPath(program_architecture)
        self.CopyDefaultDataToProgramDir(program_architecture, program_dir)

        if self.m_system_info.m_os_type == LINUX:
            ProgramInstaller.Linux.Install(program_dir, program_architecture)
        elif self.m_system_info.m_os_type == WINDOWS:
            ProgramInstaller.Windows.Install(program_dir, program_architecture)

    def GetProgramDirPath(self, program_architecture):
        program_dir = f"{INSTALLED_PROGRAM_DIR}/{self.m_system_info.m_os_type}/{program_architecture}/"
        os.makedirs(program_dir, exist_ok=True)

        return program_dir

    def CopyDefaultDataToProgramDir(self, program_architecture, program_dir):
        MainProgramInstaller.CopyDefaultDirectoriesToProgramDir(program_dir)
        self.CopyDefaultExecutableFileToProgramDir(program_dir, program_architecture)
        MainProgramInstaller.CopyDefaultDatabaseToProgramDir(program_dir)

    @staticmethod
    def CopyDefaultDirectoriesToProgramDir(program_dir):
        images_path = os.path.join(program_dir, IMAGE_DIR)
        shutil.copytree(IMAGE_DIR, images_path)

        config_path = os.path.join(program_dir, CONFIG_DIR)
        shutil.copytree(CONFIG_DIR, config_path)

        log_files_path = os.path.join(program_dir, LOG_FILES_DIR)
        shutil.copytree(LOG_FILES_DIR, log_files_path)

    def CopyDefaultExecutableFileToProgramDir(self, program_dir, program_architecture):
        executable_file_path = None
        if self.m_system_info.m_os_type == LINUX:
            executable_file_path = f"{BUILD_DIR}/{self.m_system_info.m_os_type}/{CMAKE_BUILD_TYPE}/{program_architecture}/{EXUCUTABLE_FILE_NAME_FOR_LINUX}"
        elif self.m_system_info.m_os_type == WINDOWS:
            executable_file_path = f"{BUILD_DIR}/{self.m_system_info.m_os_type}/{CMAKE_BUILD_TYPE}/{program_architecture}/{CMAKE_BUILD_TYPE}/{EXUCUTABLE_FILE_NAME_FOR_WINDOWS}"

        shutil.copy(executable_file_path, program_dir)

    @staticmethod
    def CopyDefaultDatabaseToProgramDir(program_dir):
        database_dir_path = os.path.join(program_dir, DATABASE_DIR)
        os.makedirs(database_dir_path, exist_ok=True)
        shutil.copy(DATABASE_FILE_PATH, database_dir_path)
