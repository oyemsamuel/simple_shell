# simple_shell
this project is on a simple shell created by oyem samuel and frank ikoro almond

user interaction through a command-line interface.

# Features
The Simple Shell includes the following features:

Command execution: The shell supports the execution of both built-in commands and external commands available in the system's PATH.
Built-in commands: Several built-in commands, such as exit, env, cd, setenv, unsetenv, help, history, and alias, are provided for basic system interaction.
Command chaining: The shell supports command chaining using && (logical AND) and || (logical OR) operators.
History management: The shell maintains a history of executed commands and provides the ability to access and replay them.
Alias management: Users can define and use command aliases to simplify the execution of frequently used commands.
Environment variable manipulation: The shell allows users to view, set, and unset environment variables.
Getting Started
To run the Simple Shell program, follow these steps:

Clone the repository: git clone <repository_url>
Navigate to the project directory: cd simple-shell
Compile the source files: gcc -o shell *.c
Run the shell program: ./shell
You can interact with the shell by typing commands and pressing Enter. Use built-in commands like help to get more information about available features.

# Usage
The shell supports both interactive and non-interactive modes. In interactive mode, you can directly enter commands into the shell's prompt. In non-interactive mode, you can pass a script file as an argument to execute a series of commands.

# Examples:

Interactive mode: ./shell
Non-interactive mode: ./shell script.sh
Contributing
Contributions to the Simple Shell project are welcome! If you find issues, have suggestions for improvements, or want to add new features, please feel free to open an issue or create a pull request.

# License
This project is licensed under the MIT License.
