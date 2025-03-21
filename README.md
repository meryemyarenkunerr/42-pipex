# 42cursus - pipex

Pipex is a project that explores UNIX pipes by implementing a program that replicates the shell's behavior when using pipes (|). This project helps you understand inter-process communication in UNIX by redirecting input and output between multiple commands.

## Features

* The program takes four arguments: `file1`, `cmd1`, `cmd2`, and `file2`.
* It replicates the shell command: `< file1 cmd1 | cmd2 > file2`
* Executes `cmd1` using `file1` as input and passes its output to `cmd2`, writing the final output to `file2`.
* Utilizes system calls like `open`, `close`, `read`, `write`, `fork`, `pipe`, `dup2`, and `execve`.
* Error handling ensures proper memory management and prevents crashes due to segmentation faults, bus errors, or memory leaks.

## Usage

1. Compile the project using: `make`
2. Run the program with: `./pipex file1 "cmd1" "cmd2" file2`.
    This should be equivalent to: `< file1 cmd1 | cmd > file2`