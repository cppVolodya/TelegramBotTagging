import enum

from scripts.data.main_data import *


class User:
    S_PROGRAM_ARCHITECTURES = [X32, X64]

    class BuildMode(enum.Enum):
        M_DEFAULT = 1
        M_CUSTOM  = 2
        M_ALL     = 3

    def __init__(self, vcpkg_path = None, build_mode = None, program_architecture = None):
        self.m_vcpkg_path           = vcpkg_path
        self.m_build_mode           = build_mode
        self.m_program_architecture = program_architecture
