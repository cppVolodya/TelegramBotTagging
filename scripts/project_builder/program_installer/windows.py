import os
import shutil

from scripts.data.main_data import *


class Windows:
    @staticmethod
    def Install(program_dir, program_architecture):
        Windows.CreateShortcutFile(program_dir, program_architecture)
        Windows.CopyLibrariesToProgramDirectory(program_dir, program_architecture)
        Windows.InstallShortcutFileInDesktop(program_dir, program_architecture)

    @staticmethod
    def CreateShortcutFile(program_dir, program_architecture):
        import win32com.client

        shortcut_file_name = SHORTCUT_FILE_NAME_FOR_WINDOWS_X32 if program_architecture == X32 else SHORTCUT_FILE_NAME_FOR_WINDOWS_X64
        shortcut_file_path = os.path.join(program_dir, shortcut_file_name)

        icon_file_path = os.path.abspath(program_dir + f"{IMAGE_DIR}/{IMAGE_FILE_NAME_FOR_WINDOWS}")
        exucutable_file_path = os.path.abspath(program_dir + EXUCUTABLE_FILE_NAME_FOR_WINDOWS)

        shortcut = win32com.client.Dispatch("WScript.Shell").CreateShortCut(shortcut_file_path)
        shortcut.TargetPath = exucutable_file_path
        shortcut.IconLocation = icon_file_path
        shortcut.save()

    @staticmethod
    def CopyLibrariesToProgramDirectory(program_dir, program_architecture):
        libraries_dir_path = None
        if program_architecture == X32:
            libraries_dir_path = PATH_TO_LIBRARY_BIN_OF_OPENSSL_FOR_WINDOWS_X32
        elif program_architecture == X64:
            libraries_dir_path = PATH_TO_LIBRARY_BIN_OF_OPENSSL_FOR_WINDOWS_X64

        for library_file in os.listdir(libraries_dir_path):
            if library_file.endswith(".dll"):
                library_file_path = os.path.join(libraries_dir_path, library_file)
                shutil.copy(library_file_path, program_dir)

    @staticmethod
    def InstallShortcutFileInDesktop(program_dir, program_architecture):
        desktop_dir_path = Windows.GetDesktopDirPath()
        shortcut_file_name = SHORTCUT_FILE_NAME_FOR_WINDOWS_X32 if program_architecture == X32 else SHORTCUT_FILE_NAME_FOR_WINDOWS_X64
        shortcut_file_path = os.path.join(program_dir, shortcut_file_name)
        shutil.copy(shortcut_file_path, desktop_dir_path)

    @staticmethod
    def GetDesktopDirPath():
        import win32com.client

        shell = win32com.client.Dispatch("WScript.Shell")
        desktop_dir_path = shell.SpecialFolders(DESKTOP_DIR)
        return desktop_dir_path
