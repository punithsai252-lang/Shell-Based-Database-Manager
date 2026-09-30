# Shell Based Database Manager

## Project Overview

**Shell Based Database Manager** is a command-line database management system developed in **C programming language** for Linux/Ubuntu.

The project combines concepts from Operating Systems, Systems Programming, C Programming, Command-Line Interfaces, Process Management, Inter-Process Communication, Dynamic Memory Management, Signal Handling, Modular Programming, and Memory Testing.

The system provides an interactive shell where users can perform database operations and execute Linux/system commands.

---

## Objectives

- Implement an interactive command-line database manager.
- Handle and process user commands.
- Tokenize and parse commands.
- Implement database operations.
- Support Linux/system commands.
- Implement process creation and execution.
- Implement signal handling.
- Implement inter-process communication using pipes.
- Manage dynamically allocated memory.
- Perform memory testing.
- Maintain a modular C programming structure.
- Use Git and GitHub for version control.

---

## Features

### Database Commands

- `create`
- `insert`
- `select`
- `show tables`
- `drop`

### System Commands

- `pwd`
- `whoami`
- `date`
- `ls`

### Process Management

- Process creation using `fork()`
- External command execution
- Parent-child process management
- Process synchronization

### Signal Handling

- `SIGINT`
- `SIGCHLD`
- Ctrl+C handling
- Child-process cleanup
- Zombie-process prevention

### Pipe Support

- Pipe operator `|`
- Pipe creation using `pipe()`
- Inter-Process Communication
- Connecting command output to another command's input

### Memory Testing

- AddressSanitizer support
- Valgrind testing
- Memory leak detection
- Heap allocation/deallocation testing

---

## Command Processing Workflow

```text
User Input
    ↓
Input Handling
    ↓
Command Parsing
    ↓
Tokenization
    ↓
Command Identification
    ↓
Built-in / Database / System Command
    ↓
Process Execution
    ↓
Pipe / Signal Handling
    ↓
Command Output
---

## Command Processing Workflow

```text
User Input
    ↓
Input Handling
    ↓
Command Parsing
    ↓
Tokenization
    ↓
Command Identification
    ↓
Built-in / Database / System Command
    ↓
Process Execution
    ↓
Pipe / Signal Handling
    ↓
Command Output
                 +----------------------+
                 |      User Input      |
                 +----------+-----------+
                            |
                            v
                 +----------------------+
                 |    Input Handling    |
                 +----------+-----------+
                            |
                            v
                 +----------------------+
                 |  Parser / Tokenizer  |
                 +----------+-----------+
                            |
              +-------------+-------------+
              |                           |
              v                           v
      +---------------+           +---------------+
      | Built-in / DB |           | External Cmd  |
      |   Commands    |           |   Execution   |
      +-------+-------+           +-------+-------+
              |                           |
              v                           v
      +---------------+           +---------------+
      | Database      |           | fork / exec   |
      | Operations    |           | Process Mgmt  |
      +---------------+           +---------------+

                    Process Control
                           |
                 +---------+---------+
                 |                   |
              Signals              Pipes
                 |                   |
           SIGINT / SIGCHLD        pipe()

           Shell-Based-Database-Manager/
│
├── bin/
│   └── shellforge
│
├── docs/
│   └── .gitkeep
│
├── include/
│   ├── builtin.h
│   ├── database.h
│   ├── input.h
│   ├── parser.h
│   ├── process.h
│   ├── shell.h
│   └── signals.h
│
├── screenshots/
│   └── .gitkeep
│
├── src/
│   ├── builtin.c
│   ├── database.c
│   ├── input.c
│   ├── main.c
│   ├── parser.c
│   ├── process.c
│   ├── signals.c
│   └── pipes.c
│
├── tests/
│   ├── parser_test
│   └── parser_test.c
│
├── .gitignore
├── Makefile
└── README.md
