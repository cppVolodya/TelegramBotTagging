import platform
import multiprocessing

import scripts.data as Data

from scripts.utilities import ValidateValueFromList
from scripts.data.main_data import *


class System:
    @staticmethod
    def InteractWithSystem():
        system_data = Data.System()

        system_data.m_processor_architecture = System.GetProcessorArchitecture()
        system_data.m_os_type                = System.GetOSType()
        system_data.m_number_of_threads      = System.GetNumberOfThreads()

        return system_data

    @staticmethod
    def GetProcessorArchitecture():
        processor_architecture = platform.machine().lower()

        if ValidateValueFromList(processor_architecture, Data.System.S_PROCESSORS_ARCHITECTURES_X32):
            return X32
        elif ValidateValueFromList(processor_architecture, Data.System.S_PROCESSORS_ARCHITECTURES_X64):
            return X64
        else:
            print("Unknown processor architecture for this project project: " + platform.machine())
            print(f"Set default processor architecture: {X32}")

        return "x32"

    @staticmethod
    def GetOSType():
        os_type = platform.system().lower()
        if ValidateValueFromList(os_type, Data.System.S_OS_TYPES):
            return os_type
        else:
            raise ValueError("Unsupported operating system: " + os_type)

    @staticmethod
    def ValidateNumberOfThreads(num_threads):
        if num_threads > 0:
            return True

        return False

    @staticmethod
    def GetNumberOfThreads():
        num_threads = multiprocessing.cpu_count()
        if System.ValidateNumberOfThreads(num_threads):
            return num_threads
        else:
            raise ValueError("Invalid number of CPU threads: " + str(num_threads))
