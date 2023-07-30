
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

![BotIcon](https://github.com/cppVolodya/tasks/assets/103601559/c6e60358-1154-4057-b6bf-e79ba8a66996)

## Logo

![LogoIcon](https://github.com/cppVolodya/tasks/assets/103601559/f7af9392-63b7-4dbf-8bfa-c75fcaa93f5a)

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

https://github.com/cppVolodya/tasks/assets/103601559/ed2bc787-28ac-4d3b-94ae-f5f84bc9b622

- Rejection of initial requests from users:

https://github.com/cppVolodya/tasks/assets/103601559/0d2475b0-52ca-4f96-8e35-51cc4a9f91b6

- Interaction with the bot in a private chat:

https://github.com/cppVolodya/tasks/assets/103601559/bc07e012-e7ef-4a42-b7fe-3d9b11c1ee4b

- Сommand start:

https://github.com/cppVolodya/tasks/assets/103601559/2b5e7528-07a4-4513-ab23-620d3a0f53a0

- Сommand help:

https://github.com/cppVolodya/tasks/assets/103601559/3a231a57-8a1a-439b-84e2-186bba1a4221

- Сommand sign:

https://github.com/cppVolodya/tasks/assets/103601559/738314e8-293d-4b06-9925-9fda225a1d1f

- Command tag:

https://github.com/cppVolodya/tasks/assets/103601559/0685978a-31f3-4c5c-b40b-3db7e11950e7

- Command settings:

https://github.com/cppVolodya/tasks/assets/103601559/ddfdd8ed-1d69-49a5-8c61-8b7210945379

- Log file data:

https://github.com/cppVolodya/tasks/assets/103601559/6c805963-103b-4169-b65f-90488111e290

- Database display:

https://github.com/cppVolodya/tasks/assets/103601559/8a475bbd-ffb6-45f3-9de6-1138f9a7908f

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
