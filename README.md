# Shell Based Database Manager

## Project Overview

The **Shell Based Database Manager** is a command-line database management system developed using **C programming on Linux/Ubuntu**.

The project demonstrates concepts from:

- Operating Systems
- Systems Programming
- C Programming
- Command Processing
- Dynamic Memory Management
- Modular Programming
- Process Execution
- Signal Handling
- Process Control

The system provides an interactive command-line interface where users can perform database operations and execute selected Linux/system commands.

---

## Project Objectives

- Develop an interactive command-line database manager.
- Implement command input and parsing.
- Tokenize user commands for processing.
- Implement basic database operations.
- Support selected Linux/system commands.
- Use modular C programming.
- Demonstrate process execution in Linux.
- Implement signal handling.
- Prevent zombie child processes.
- Maintain the project using Git and GitHub.

---

## Features

### Database Operations

- `create`
- `insert`
- `select`
- `show tables`
- `drop`

### Built-in Commands

- `help`
- `pwd`
- `whoami`
- `date`
- `ls`
- `exit`

### Process Execution

The project supports execution of external Linux commands using process creation and execution concepts.

The system uses:

- `fork()`
- `execvp()`
- `waitpid()`

to manage child processes.

### Signal Handling

Week 6 introduces signal handling for:

- `SIGINT`
- `SIGCHLD`

The system handles `Ctrl+C` without immediately terminating the database manager and reaps completed child processes to prevent zombie processes.

---

## System Architecture

```text
                         USER
                           |
                           v
                  COMMAND LINE INPUT
                           |
                           v
                    COMMAND PARSER
                           |
                           v
                   COMMAND DISPATCHER
                     /            \
                    /              \
                   v                v
          DATABASE MODULE      BUILTIN /
                               PROCESS MODULE
                |                  |
                v                  v
       DATABASE OPERATIONS    SYSTEM COMMANDS
                \                  /
                 \                /
                  \              /
                       v
                     OUTPUT
create students
tokens[0] = create
tokens[1] = students
show tables
tokens[0] = show
tokens[1] = tables
