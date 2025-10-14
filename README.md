This project is a custom implementation of a shell, similar to `bash` or `zsh`. It is a school project that aims to create a simple yet functional command-line interpreter.

## About The Project

The Minishell project is a classic exercise in system programming. It involves parsing user input, managing processes, and interacting with the operating system's kernel. This implementation is written in C and uses the `readline` library for input handling.

The project is structured into several modules:

-   `shell/`: Core shell functionality, history, and utilities.
-   `environment/`: Environment variable management.
-   `runtime/`: Command execution, redirection, and expansion.
-   `lexical_a/`: Lexical analysis and tokenization.
-   `syntax_a/`: Syntax analysis and here-doc handling.
-   `builtins/`: Implementation of built-in commands like `cd`, `echo`, `pwd`, etc.
-   `optimization/`: Command and here-doc optimization.
-   `library/`: Contains `libft` and `get_next_line`.

## How To Install

To get a local copy up and running, follow these simple steps.

### Prerequisites

You need to have `git` and `make` installed on your system. You also need the `readline` library.

On Debian/Ubuntu, you can install it with:
```cli
sudo apt-get install libreadline-dev
```

### Installation

1.  Clone the repo
    ```cli
    git clone https://your_repo_link/minishell.git
    ```
2.  Navigate to the project directory
    ```cli
    cd minishell
    ```
3.  Compile the project
    ```cli
    make
    ```

This will create the `minishell` executable in the root directory.

## How To Use

To start the shell, run the following command:

```cli
./minishell
```

You will be greeted with a new prompt, ready to accept your commands.

### Examples

Here are some examples of what you can do with Minishell:

-   **Simple commands**
    ```cli
    ls -l
    ```

-   **Pipes**
    ```cli
    cat file1 | grep "hello"
    ```

-   **Redirections**
    ```cli
    ls > file.txt
    cat < file.txt
    ```

-   **Here-doc**
    ```cli
    cat << EOF
    hello
    world
    EOF
    ```

-   **Built-in commands**
    ```cli
    echo "Hello, World!"
    cd /path/to/dir
    pwd
    export VAR="value"
    unset VAR
    env
    exit
    ```

## Cleaning Up

To remove the object files, run:
```cli
make clean
```

To remove the object files and the `minishell` executable, run:
```cli
make fclean
``` 
