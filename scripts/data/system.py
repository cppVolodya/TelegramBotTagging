from scripts.data.main_data import *


class System:
    S_PROCESSORS_ARCHITECTURES_X64 = ["x64", "amd64", "x86_64"]
    S_PROCESSORS_ARCHITECTURES_X32 = ["x86", "i386", "i686", "amd32", "x32"]

    S_OS_TYPES = [LINUX, WINDOWS]

    def __init__(self, processor_architecture = None, os_type = None, number_of_threads = None):
        self.m_processor_architecture = processor_architecture
        self.m_os_type                = os_type
        self.m_number_of_threads      = number_of_threads
