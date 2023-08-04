
# Telegram Bot Tagging


## Roadmap

- About
- Logo
- Acknowledgments
- Tech
- Demo
- Installation
- Run locally
- Documentation
- Additional information

## About

"Telegram Bot Tagging" is a Telegram bot server designed to mention or tag users in a group.

![BotIcon](https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/4e0715f3-3d2e-4167-9054-1975d0b0ae5e)

## Logo

![LogoIcon](https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/e7af3872-975c-46c2-8410-bfaebc633149)

## Acknowledgements

 - [Logo maker](https://looka.com/logo-maker/)
 - [Library tgbot-cpp](https://github.com/reo7sp/tgbot-cpp/tree/master)
 - [Library BS::thread_pool](https://github.com/bshoshany/thread-pool)
 - [Library SQLiteCpp](https://github.com/SRombauts/SQLiteCpp)
 - [Library OpenSSL](https://www.openssl.org/)

## Tech Stack

- C++(v17)
- Telegram Bot API(v6.4)
- vcpkg(v2023.07.21-1)
- tgbot-cpp(Boost, OpenSSL, libcurl, v1.6)
- OpenSSL(v3.1.2)
- SQLiteCpp(SQLite, sqlite3, v3.3.0)
- BS::thread_pool(v3.5.0)
- python(pyinstaller, pywin32, winshell, v3.11.3)
- cmake(v3.22.1)
- SQLite(3.42.0)
- compiler Visual Studio(v17 2022)
- builder MSBuild(v17 2022)
- compiler gcc(c, c++, v13.2.1)
- builder Unix Makefiles(v4.4.1)
- operating systems(Windows, Linux)

## Demo

- Initial launch of the program(request a token and save it):

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/28abbf89-be21-4adc-b6be-ea17b1892121

- Rejection of initial requests from users:

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/0298de22-f0a4-4746-8a30-093a77748be2

- Interaction with the bot in a private chat:

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/b64ccee8-d2b4-4638-a40a-922498407d8e

- Сommand start:

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/6cfd892e-246c-4d17-896c-7b8484b2bc75

- Сommand help:

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/f1497343-3dca-4eb2-a83b-776840993472

- Сommand sign:

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/89e2da16-e535-4e5d-890a-1ec2bc80cdcd

- Command tag:

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/95c53488-8b54-4269-8da3-5198f1fd6789

- Command settings:

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/08a19145-8985-41e4-a7ae-ac3cd55eea79

- Log file data:

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/c2a96d45-4b78-4306-a202-cca9845dfbad

- Database display:

https://github.com/cppVolodya/TelegramBotTagging/assets/103601559/4afa79a0-91a2-401e-b9a6-658111aa0a48

## Installation

#### To install the project yourself, you must follow the following instructions:

1. Clone the current project or download the rar or zip file via GitHub:

```bash
  git: git clone https://github.com/cppVolodya/TelegramBotTagging.git

  WinRar: cod->Download ZIP(don't forget to unzip)
```

2. Go to the project directory:

```bash
  telegram_bot_tagging/
```

3. [Builder Telegram Bot Tagging](https://github.com/cppVolodya/BuilderTelegramBotTagging.git) - Follow the link to first download the required project dependencies and build it

4. Then, after building the project, you can run the program and follow the next instructions(setting up the Telegram bot) of the program.

#### Regarding the second point, namely the setting of the Telegram bot, you can refer to the additional information, which is at the very bottom.

## Run Locally

#### In order not to build the project, you can use ready-made binary (executable) files, for this you need to follow the following steps:

1. Clone the current project or download the rar or zip file via GitHub:

```bash
  git: git clone https://github.com/cppVolodya/TelegramBotTagging.git

  WinRar: cod->Download ZIP(don't forget to unzip)
```

2. Go to the program directory:

```bash
  telegram_bot_tagging/program/windows
```

3. Select the application architecture:

```bash
  telegram_bot_tagging/program/windows/x32
                      or
  telegram_bot_tagging/program/windows/x64
```

4. Run the program or the shortcut.

```bash
  telegram_bot_tagging.exe
                      or
  Telegram Bot Tagging[x32, x64].lnk
```

5. Then, after launching the program, you must follow the further instructions (Telegram bot setup) of the program.
```bash
Regarding the creation and configuration of the Telegram bot,
you can refer to the additional information, which is located at the very bottom.
```

#### You can copy the shortcut "Telegram Bot Tagging[x32, x64].lnk" to the desktop.

## Documentation

#### Information about the function of each Telegram bot command:

- /start - this command allows you to get general information about the bot. You will receive information such as: firstname, username, about, description, group privacy, commands(as well as a brief description of each command) and description picture.

- /help - This command provides you with detailed help and instructions for using the bot. You will learn about all the available commands and their purpose in a broad description.

- /settings - with this command you can select the users you want to tag. A list of selected users to tag or mention will be provided and a panel will open where you can select users by clicking on buttons, clicking on a specific user will automatically add or remove it from the list. A \"Default\" button will also be available, which will perform the function of resetting the default settings, that is, all registered users will be selected for tagging.

- /sign - This command allows you to log into the bot. With the help of this command, you can be tagged or mentioned in the group.

- /tag [text] - This command allows you to tag all selected users with or without text. Just type /tag and then optionally type the text you want to include in the message to be tagged.

## Additional information

#### To simplify the creation and configuration of your Telegram bot, you can use this information:

- firstname: TagBot(voluntarily)
- username: tag_cpp_bot(voluntarily)
- about: This bot is designed to mention or tag users in a group.
- description: This Telegram bot provides a simple and effective feature to mention or tag users in a group. It will further increase organization and simplify communication, allowing you to quickly address selected groups of participants.
- description picture: згенероване зображення + слоган "@ + Easy tagging"
- botpic: згенероване зображення
- commands:
    - start - Get general information about the bot.
    - help - Get help and instructions for using the bot.
    - settings - Select users to be tagged.
    - sign - Sign in to the bot.
    - tag - Tag all selected users with or without text: /tag [text].
