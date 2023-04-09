// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "console_interface.hpp"
#include "error/messages.hpp"
#include "utilities.hpp"


namespace N_TelegramBotTagging
{
UserData ConsoleInterface::InteractWithUser()
{
	std::string api_token;
	bool reading_success{ConsoleInterface::TryReadingApiTokenFromFile(&api_token)};
	if(not reading_success)
	{
		api_token = ConsoleInterface::ReadingApiTokenFromConsole();

		bool query_result{ConsoleInterface::AskUserToSaveApiToken()};
		if(query_result)
		{
			this->SaveApiTokenInFile(api_token);
		}
	}

	ConsoleInterface::DisplayInformation();

	UserData user_data;
	user_data.GetBotInfo().SetApiToken(api_token);

	return user_data;
}

bool ConsoleInterface::TryReadingApiTokenFromFile(std::string *api_token)
{
	std::ifstream file(S_DEFAULT_FILE_WITH_API_TOKEN.data());
	bool result = true;

	constexpr std::size_t capacity_of_api_token{50UL};
	api_token->reserve(capacity_of_api_token);

	if (file.is_open())
	{
		file >> *api_token;
		if(api_token->empty())
		{
			result = false;
		}
	}
	else
	{
		result = false;
	}

	return result;
}

std::string ConsoleInterface::ReadingApiTokenFromConsole() noexcept
{
	std::cout << "Hi, I'm a Telegram bot program that was created for"
				 "tagging (mentioning) selected group members.\n"
				 "I am not suitable for channels and private chats, only for groups.\n"
				 	"To run telegram bot, you need to enter API token,"
				 "if you don't know how to get API token, below are the steps to get it:\n\n"

				 "Step 1. Open Telegram messenger, sign in to your account or create a new one.\n"
				 "Step 2. Enter @Botfather in the search tab and choose this bot.\n"
				 "Step 3. Click “Start” to activate BotFather bot."
				 	"In response, you receive a list of commands to manage bots.\n"
				 "Step 4. Choose or type the /newbot command and send it.\n"
				 "Step 5. Choose a name for your bot - your subscribers will see it in the conversation.\n"
				 "And choose a username for your bot - the bot can be found by its username in searches.\n"
				 "The username must be unique and end with the word 'bot'.\n\n"

				 "After choosing a suitable name for your bot, the bot is created.\n"
				 "You will receive a message with a link to your bot t.me/<bot_username>,\n"
				 "recommendations for setting up your profile picture,\n"
				 	"a description and a list of commands to control your new bot,"
				 "and you will also receive an API token.\n\n"

				 "Copy the API token value and enter it in the given field: ";

	std::string api_token;
	std::cin >> api_token;

	return api_token;
}

bool ConsoleInterface::AskUserToSaveApiToken()
{
	std::cout << "\nDo you want to save the API token(yes or no): ";

	std::string answer;
	std::cin >> answer;

	std::string lower_case_answer{answer};
	(void)std::transform(lower_case_answer.begin(), lower_case_answer.end(),
						 lower_case_answer.begin(), ::tolower);

	bool result{true};
	if(lower_case_answer != "yes" and
	   lower_case_answer != "y"   and
	   lower_case_answer != "ye")
	{
		result = false;
		std::cout << "\nThe API token is not saved, every time you start the Telegram bot,\n"
					 "you will have to enter the API token.\n\n";
	}

	return result;
}

void ConsoleInterface::SaveApiTokenInFile(const std::string_view api_token)
{
	std::ofstream file{S_DEFAULT_FILE_WITH_API_TOKEN.data()};

	if (file.is_open())
	{
		file << api_token;
		std::cout << "\nAPI token saved to file: 'api_token.txt'\n"
					 "Every time you start the Telegram bot, you will not have to enter the API token,\n"
					 "because it is saved. If you want to change the API token,\n"
					 "you will need to find the 'api_token.txt' "
					 "file in the directory with the telegram bot program and edit it,\n"
					 "replacing the old API token with the new one.\n\n";
	}
	else
	{
		std::cout << N_Error::N_Messages::G_MINOR << " "
				  << N_Error::N_Messages::G_LOG_FILE_HINT << "\n" << std::endl;

		std::string message
			= N_TelegramBotTagging::N_Utilities::CreateMessageForExceptionErrorWritingDataToFile(ConsoleInterface::S_DEFAULT_FILE_WITH_API_TOKEN,
																								 api_token);

		this->m_logger->AppendErrorsData(message);
	}
}

void ConsoleInterface::DisplayInformation() noexcept
{
	std::cout << "The Telegram bot program stores three types of information.\n"
				 "The first type of information is recorded in the first log file\n"
				 "with the name 'program_status.log' and reflects the working capacity of the program.\n"
				 "The second type of information is written to the second log file named 'user_requests.log'\n"
				 "and displays the requests sent to the bot.\n"
				 "And the third type of information is written to the third log file named 'errors.log'\n"
				 "and contains information about program errors.\n"
				 "All three types of information recorded in log files are updated periodically, every 10 seconds.\n\n";
}
}  // namespace N_TelegramBotTagging
