# Linux System Programming (LSP)

This repository contains a collection of projects and exercises focused on Linux system programming. It aims to provide hands-on experience with key concepts in operating systems, process management, memory management, and more, using C and system-level programming techniques.

## Contents

- **Process Management**: Programs to create, manage, and terminate processes.
- **Memory Management**: Examples of memory allocation, deallocation, and handling in Linux.
- **Interprocess Communication**: Implementation of pipes, message queues, and shared memory for communication between processes.
- **Multithreading**: Examples using pthreads for concurrent execution.
- **Signal Handling**: Programs to demonstrate how signals are used and managed in Linux.
- **File I/O Operations**: Handling file operations using system calls.
- **Networking**: Basic networking programs like client-server applications using sockets.

## Projects

- **Pipe Program (`pipe.c`)**: Demonstrates the use of pipes for interprocess communication.
- **Fork and Exec (`fork-exec.c`)**: Shows how to fork processes and execute programs.
- **TCP Server (`tcp-server.c`)**: A basic TCP server program demonstrating socket programming.
- **Multithreading (`thread-mutex-multiple-client.c`)**: A multithreaded server to handle multiple clients simultaneously.
- **Signal Handling (`signal-handle-SIGINT.c`)**: Shows how to handle signals like `SIGINT` (Ctrl+C).
- **Mutex (`thread-mutex.c`)**: Demonstrates using mutexes for thread synchronization.

## Requirements

To build and run these programs, you need:

- A Linux-based system.
- A C compiler (e.g., GCC)
- Basic knowledge of Linux system programming

## How to Compile

To compile any program in this repository, use the following command:

```bash
gcc -o <output-file> <source-file>.c

