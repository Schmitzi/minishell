# Minishell<br>
## Overview<br>
<br>
Minishell is a project developed as part of the 42 School curriculum. The goal of this project is to create a simple shell that mimics the behavior of a Unix-like command-line interface. The project is designed to deepen understanding of process management, signal handling, and the intricacies of the shell environment.
Features

- Basic Shell Commands: Supports execution of basic commands such as ls, echo, cat, etc.
- Pipes and Redirections: Implements piping (|) and redirection (>, <) for handling input and output between commands.
- Environment Variables: Manages and manipulates environment variables like PATH, HOME, etc.
- Signal Handling: Handles signals such as Ctrl+C (SIGINT) and Ctrl+D (EOF) gracefully.
- Custom Built-ins: Includes built-in commands like cd, export, unset, env, exit, etc.
- Error Handling: Provides basic error handling and messaging for invalid commands or syntaxes.

## Usage

Compile the project using the provided Makefile:

```bash
make
```

Start the shell by running:

```bash
./minishell
```

You can then use the shell like a regular terminal to execute commands, manage files, and more.
Requirements

- C Language: The project is written in C.
- Makefile: Provided for easy compilation.
- Unix-like Operating System: Developed and tested on Linux/Unix environments.

Learning Outcomes

Through this project, I've gained a deeper understanding of:

- Process creation and management.
- Signal handling in Unix.
- Command parsing and execution flow.
- Implementing a user-space program that interacts directly with the OS.

Contributors

This project was completed as part of the curriculum at 42 School.
