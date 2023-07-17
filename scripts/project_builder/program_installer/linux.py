import os
import shutil

from scripts.data.main_data import *


class Linux:
    @staticmethod
    def Install(program_dir, program_architecture):
        Linux.CreateDesktopFile(program_dir, program_architecture)
        Linux.InstallDesktopFile(program_dir, program_architecture)
        Linux.SetFilePermissions(program_dir, program_architecture)

    @staticmethod
    def CreateDesktopFile(program_dir, program_architecture):
        desktop_file_name = DESKTOP_FILE_NAME_FOR_LINUX_X32 if program_architecture == X32 else DESKTOP_FILE_NAME_FOR_LINUX_X64
        desktop_file_path = os.path.join(program_dir, desktop_file_name)
        with open(desktop_file_path, "w") as desktop_file:
            desktop_file.write(f'\n'
                               f'[Desktop Entry]\n'
                               f'Type = Application\n'
                               f'Version = 1.0\n'
                               f'Name = Telegram Bot Tagging\n'
                               f'Comment = A program that controls the launch of a'
                               f'Telegram bot for tagging group members\n'
                               f'Path = {os.path.abspath(program_dir)}\n'
                               f'Exec = {os.path.abspath(program_dir + EXUCUTABLE_FILE_NAME_FOR_LINUX)}\n'
                               f'Icon = {os.path.abspath(program_dir + f"{IMAGE_DIR}/{IMAGE_FILE_NAME_FOR_LINUX}")}\n'
                               f'Terminal=true\n'
                               f'Categories=Telegram;Bot;C++;Application;Tagging;\n')

    @staticmethod
    def InstallDesktopFile(program_dir, program_architecture):
        desktop_file_name = DESKTOP_FILE_NAME_FOR_LINUX_X32 if program_architecture == X32 else DESKTOP_FILE_NAME_FOR_LINUX_X64
        desktop_file_path = os.path.join(program_dir, desktop_file_name)

        Linux.InstallDesktopFileInLocalShareApplications(desktop_file_path)
        Linux.InstallDesktopFileInDesktop(desktop_file_path)

    @staticmethod
    def InstallDesktopFileInLocalShareApplications(desktop_file_path):
        local_share_applications_dir_path = Linux.GetLocalShareApplicationsDirPath()
        shutil.copy(desktop_file_path, local_share_applications_dir_path)

    @staticmethod
    def InstallDesktopFileInDesktop(desktop_file_path):
        desktop_dir_path = Linux.GetDesktopDirPath()
        shutil.copy(desktop_file_path, desktop_dir_path)

    @staticmethod
    def SetDesktopFilePermissions(desktop_file_path):
        os.system(f'gio set "{desktop_file_path}" metadata::trusted true 2>"/dev/null"')
        os.system(f'chmod a+x "{desktop_file_path}"')

    @staticmethod
    def SetFilePermissions(program_dir, program_architecture):
        exucutable_file_path = os.path.join(program_dir, EXUCUTABLE_FILE_NAME_FOR_LINUX)

        os.system(f'chmod a+x "{exucutable_file_path}"')

        desktop_file_name = DESKTOP_FILE_NAME_FOR_LINUX_X32 if program_architecture == X32 else DESKTOP_FILE_NAME_FOR_LINUX_X64
        desktop_file_path_program_dir                  = os.path.join(program_dir, desktop_file_name)
        desktop_file_path_local_share_applications_dir = os.path.join(Linux.GetLocalShareApplicationsDirPath(), desktop_file_name)
        desktop_file_path_desktop_dir                  = os.path.join(Linux.GetDesktopDirPath(), desktop_file_name)

        Linux.SetDesktopFilePermissions(desktop_file_path_program_dir)
        Linux.SetDesktopFilePermissions(desktop_file_path_local_share_applications_dir)
        Linux.SetDesktopFilePermissions(desktop_file_path_desktop_dir)

    @staticmethod
    def GetHomeDirPath():
        return os.path.expanduser("~")

    @staticmethod
    def GetDesktopDirPath():
        return os.path.join(Linux.GetHomeDirPath(), DESKTOP_DIR)

    @staticmethod
    def GetLocalShareApplicationsDirPath():
        return os.path.join(Linux.GetHomeDirPath(), LOCAL_SHARE_APPLICATIONS_DIR_PATH_FOR_LINUX)
