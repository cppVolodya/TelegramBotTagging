import os
import shutil

import scripts.project_builder as ProjectBuilder

from scripts.data.main_data import *


class Cleaner:
    def __init__(self, system_data):
        self.m_system_data = system_data

    def Start(self):
        Cleaner.ClearBuild()
        self.ClearInstalledProgram()

    @staticmethod
    def ClearBuild():
        if os.path.exists(BUILD_DIR):
            shutil.rmtree(BUILD_DIR)

    @staticmethod
    def RemoveDesktopFileForLinux(path_to_file):
        desktop_file_path_x32 = os.path.join(path_to_file, DESKTOP_FILE_NAME_FOR_LINUX_X32)
        desktop_file_path_x64 = os.path.join(path_to_file, DESKTOP_FILE_NAME_FOR_LINUX_X32)
        if os.path.exists(desktop_file_path_x32):
            os.remove(desktop_file_path_x32)
        if os.path.exists(desktop_file_path_x64):
            os.remove(desktop_file_path_x64)

    @staticmethod
    def ClearInstalledProgramForLinux():
        desktop_dir_path = ProjectBuilder.ProgramInstaller.Linux.GetDesktopDirPath()
        local_share_applications_dir_path = ProjectBuilder.ProgramInstaller.Linux.GetLocalShareApplicationsDirPath()

        Cleaner.RemoveDesktopFileForLinux(desktop_dir_path)
        Cleaner.RemoveDesktopFileForLinux(local_share_applications_dir_path)

    @staticmethod
    def ClearInstalledProgramForWindows():
        desktop_dir_path = ProjectBuilder.ProgramInstaller.Windows.GetDesktopDirPath()

        shortcut_file_path_x32 = os.path.join(desktop_dir_path, SHORTCUT_FILE_NAME_FOR_WINDOWS_X32)
        shortcut_file_path_x64 = os.path.join(desktop_dir_path, SHORTCUT_FILE_NAME_FOR_WINDOWS_X32)

        if os.path.exists(shortcut_file_path_x32):
            os.remove(shortcut_file_path_x32)
        if os.path.exists(shortcut_file_path_x64):
            os.remove(shortcut_file_path_x64)

    def ClearInstalledProgram(self):
        if os.path.exists(INSTALLED_PROGRAM_DIR):
            shutil.rmtree(INSTALLED_PROGRAM_DIR)

        if self.m_system_data.m_os_type == LINUX:
            Cleaner.ClearInstalledProgramForLinux()
        elif self.m_system_data.m_os_type == WINDOWS:
            Cleaner.ClearInstalledProgramForWindows()
