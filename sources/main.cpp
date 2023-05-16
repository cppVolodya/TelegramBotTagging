// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "bot_launcher.hpp"
#include "program_completion_status.hpp"


int main()
{
	N_TelegramBotTagging::BotLauncher bot_launcher;
	const auto result = bot_launcher.Start();

	(void)std::cin.get();

	if (result == N_TelegramBotTagging::ProgramCompletionStatus::critical)
	{
		exit(static_cast<int>(result));
	}

	return static_cast<int>(result);
}
