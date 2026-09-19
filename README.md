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
- Maintain the project using Git and GitHub.

---

## Features

### Database Operations

- `create`
- `insert`
- `select`
- `show tables`
- `drop`

### System / External Commands

- `pwd`
- `whoami`
- `date`
- `ls`

### Built-in Commands

The project provides built-in command handling through the command-processing architecture.

---

## Command Processing

The command-processing workflow is:

```text
User Input
    ↓
Read Command
    ↓
Command Parsing
    ↓
Tokenization
    ↓
Command Identification
    ↓
Command Dispatch
    ↓
Module Execution
    ↓
Output

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
                  /       \
                 /         \
                v           v
       DATABASE MODULE    BUILTIN /
                           PROCESS MODULE
                |              |
                v              v
       DATABASE OPERATIONS   SYSTEM COMMANDS
                \              /
                 \            /
                  v          v
                     OUTPUT

---

## Tokenization Examples

### Example 1

Input:

```text
create students
tokens[0] = create
tokens[1] = students
show tables
tokens[0] = show
tokens[1] = tables
