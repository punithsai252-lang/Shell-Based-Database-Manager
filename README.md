# Shell Based Database Manager

## Project Overview

The **Shell Based Database Manager** is a command-line database management system developed using the **C programming language** on **Ubuntu/Linux**.

The project provides a simple shell interface through which users can interact with a database using commands. It demonstrates concepts of **Operating Systems, Systems Programming, C programming, dynamic memory management, modular programming, and command processing**.

The main goal of the project is to understand how a shell can accept user commands, process the input, and perform database operations.

---

## Objectives

The main objectives of the project are:

- To develop a database manager using C.
- To provide a command-line shell interface.
- To implement basic database operations.
- To understand dynamic memory allocation.
- To implement user input handling.
- To organize the program into multiple modules.
- To compile and manage the project using Makefile.
- To use Git and GitHub for version control.

---

## Features

The Shell Based Database Manager provides the following features:

- Interactive command-line shell
- Database initialization
- Create tables
- Show available tables
- Insert records
- Select records
- Drop tables
- Dynamic user input
- Dynamic memory allocation using `malloc()`
- Dynamic memory resizing using `realloc()`
- Modular C programming
- Makefile-based compilation
- Git/GitHub project management

---

## Project Structure

```text
Shell-Based-Database-Manager/
│
├── bin/
│   └── shellforge
│
├── include/
│   ├── database.h
│   ├── input.h
│   └── shell.h
│
├── src/
│   ├── database.c
│   ├── input.c
│   └── main.c
│
├── Makefile
└── README.md
