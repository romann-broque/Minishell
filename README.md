## 📜 Minishell

Welcome to Minishell, a simple yet powerful Unix shell. Minishell provides a command-line interface with several essential features. It's designed to be intuitive and functional for everyday use.

### 🌟 Key Features

- **Command Execution**: Minishell can execute system commands based on the PATH variable or using a relative or absolute path.

- **Prompt**: It displays a prompt to indicate it's ready to accept a command.

- **Command History**: Minishell maintains a working history of previously executed commands, allowing you to recall and re-execute them easily.

- **Signal Handling**: The shell handles signals efficiently, using a single global variable to indicate received signals. This approach ensures that the signal handler won't access main data structures, maintaining the integrity of your shell.

- **Quoting**: Minishell correctly interprets single (' ') and double (" ") quotes, preventing unwanted interpretation of metacharacters within them.

- **Redirection**: You can redirect input (<) and output (>) and even implement heredoc-style input (<<) to read input until a delimiter is seen (without updating the history). Append mode (>>) for output is also supported.

- **Pipes**: Minishell allows you to use pipes (|) to connect the output of one command to the input of the next, enabling complex command chains.

- **Environment Variables**: You can work with environment variables, using the "$" symbol followed by a sequence of characters to expand to their values.

- **Exit Status**: The shell provides access to the exit status of the most recently executed foreground pipeline using "$?".

- **Interactive Mode**: In interactive mode, Minishell behaves like you would expect from a shell. You can use ctrl-C to display a new prompt, ctrl-D to exit the shell, and ctrl-\ (ctrl-backslash) to do nothing.

- **Built-in Commands**: Minishell implements several essential built-in commands, including:
    - `echo` with the `-n` option
    - `cd` with relative or absolute paths
    - `pwd` with no options
    - `export` with no options
    - `unset` with no options
    - `env` with no options or arguments
    - `exit` with no options

### 🚀 Getting Started

#### Requirements

You need first to install readline

```shell
sudo apt update
sudo apt install libreadline-dev
```

#### Compilation

To compile and run Minishell, use the provided Makefile. Here are the basic commands:

```shell
make         # Compile Minishell
./minishell  # Run Minishell
```

Enjoy using Minishell! 🐚💻
