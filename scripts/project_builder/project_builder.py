import scripts.data as Data
import scripts.interface as Interface
import scripts.project_builder as ProjectBuilder


class MainProjectBuilder:
    def __init__(self):
        self.m_system_info = Data.System()
        self.m_user_data = Data.User()

    def Start(self):
        self.m_system_info = Interface.System.InteractWithSystem()
        self.m_user_data   = Interface.Console.InteractWithUser ()
        ProjectBuilder.Cleaner(self.m_system_info).Start()

        program_architectures = self.GetProgramArchitectures()
        for program_architecture in program_architectures:
            ProjectBuilder.DataChecker                          (self.m_system_info, self.m_user_data).Start(program_architecture)
            ProjectBuilder.CmakeBuilder                         (self.m_system_info, self.m_user_data, program_architecture).Start()
            ProjectBuilder.ProgramInstaller.MainProgramInstaller(self.m_system_info).Start(program_architecture)
            ProjectBuilder.SuccessReporter                      (self.m_system_info).Start(program_architecture)

    def GetProgramArchitectures(self):
        program_architectures = None
        if self.m_user_data.m_build_mode == Data.User.BuildMode.M_DEFAULT:
            program_architectures = [self.m_system_info.m_processor_architecture]
        elif self.m_user_data.m_build_mode == Data.User.BuildMode.M_CUSTOM:
            program_architectures = [self.m_user_data.m_program_architecture]
        elif self.m_user_data.m_build_mode == Data.User.BuildMode.M_ALL:
            program_architectures = ["x32", "x64"]

        return program_architectures
