import os

import scripts.project_builder as ProjectBuilder

from scripts.data.main_data import *


class SuccessReporter:
    def __init__(self, system_data):
        self.m_system_data = system_data

    def Start(self, program_architecture):
        if self.m_system_data.m_os_type == LINUX:
            self.ReportSuccessForLinux(program_architecture)
        elif self.m_system_data.m_os_type == WINDOWS:
            self.ReportSuccessForWindows(program_architecture)

    def ReportSuccessForLinux(self, program_architecture):
        print(f"Build completed successfully for {LINUX}.")

        desktop_file_name = DESKTOP_FILE_NAME_FOR_LINUX_X32 if program_architecture == X32 else DESKTOP_FILE_NAME_FOR_LINUX_X32
        print(f"Program path: {os.path.abspath(f'{INSTALLED_PROGRAM_DIR}/{self.m_system_data.m_os_type}/{program_architecture}')}")
        print(f"Desktop file: {os.path.abspath(ProjectBuilder.ProgramInstaller.Linux.GetDesktopDirPath() + desktop_file_name)}")
        print(f"Desktop file: {os.path.abspath(ProjectBuilder.ProgramInstaller.Linux.GetLocalShareApplicationsDirPath() + desktop_file_name)}")

    def ReportSuccessForWindows(self, program_architecture):
        print(f"Build completed successfully for {WINDOWS}.")

        shortcut_file_name = SHORTCUT_FILE_NAME_FOR_WINDOWS_X32 if program_architecture == X32 else SHORTCUT_FILE_NAME_FOR_WINDOWS_X32
        print(f"Program path:          {os.path.abspath(f'{INSTALLED_PROGRAM_DIR}/{self.m_system_data.m_os_type}/{program_architecture}')}")
        print(f"Desktop Shortcut file: {os.path.abspath(ProjectBuilder.ProgramInstaller.Windows.GetDesktopDirPath() + f'/{shortcut_file_name}')}")
