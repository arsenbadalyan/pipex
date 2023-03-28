# PIPEX | 42 Yerevan

### Table of Contents
* [Introduction](#introduction)
* [Pipex in Shell](#pipex-in-shell)
* [The Pipex Algorithm](#the-pipex-algorithm)
* [Bonus](#bonus)
  * [Multiple Pipes](#multiple-pipes)
  * [Here Document](#here-document)
* [Installation](#installation)
* [Summary](#summary)

## Introduction

In this projec't we'll make our own implementation of the pipes we know and love from shell (``|``). To do so, we will start using a whole new set of functions that will introduce to us the concept of multiple processes, using pipes, forks and dups.

## Pipex in Shell

In this project we are asked to code a program which will immitate the behavior of this shell command:

```shell
❯ < file1 cmd1 | cmd2 > file2
```
The idea of the program is that we take an infile and two commands, and pass the infile as the standard input to the first command, and then pipe the output of the first command to the second command, and finally save it all to a second file. Now that we've seen the command, let's break it down:

* ``<``: Used to denote that we will be passing the next argument as the standard input (stdin)
* ``file1``: Path to the file we want to open as the standard input. It must exist and should be opened read-only
* ``cmd1``: First command. It will receive the stdin and run a command with it, if applicable
* ``|``: Transforms the standard output (stdout) of the first command into the standard input (stdin) for the next command
* ``cmd2``: Receives the standard output of the first command as stdin and runs a command with it, if applicable
* ``>``: Redirects whatever is on the standard output (stdout) into a file, creating it if it does not exist
* ``file2``: Path to an output file which may or may not exist. If it exists, it will be truncated (emptied) and should be opened write-only

## The Pipex Algorithm

Our own implementation of the previous command will have a similar look. We will compile an executable called ``pipex``, which will only accept 4 commands in the mandatory part. This is what it expects to receive:

```shell
❯ ./pipex file1 cmd1 cmd2 file2
```

As mentioned before, this project is done with the help of a new set of tools: pipes, forks and dups, among others. Here's a brief description of what these functions do:

| Function | Descripton | Return Value |
| :-------:| :---------:| :----------: |
| ``pipe(fd)`` | Recives a ``fd[2]`` and opens ``fd[0]`` for reading and ``fd[1]`` for writing | ``-1`` on error |
| ``fork()`` | Splits process creating a child process with pid ``0`` | Process id of both processess (child = ``0``, parent > ``0``), ``-1`` on error |
| ``dup2(oldfd, newfd)`` | Closes ``newfd`` if needed, then duplicates ``oldfd`` into ``newfd`` | ``-1`` on error |
| ``execve(path, cmd, envp)`` | Receives full path of executable, NULL-terminated array of parameters, and environment. Replaces current process with that of the specified command | ``-1`` on error |


1) The first thing we had to do was obtain the path for the commands we recived as parameters. To do so we look at the ``PATH`` variable found on unix-based systems. We store both the full path and the array of parameters as the nodes of a linked list for easier access later.

2) After having all the commands conveniently stored and after some very rigurous error checking, we iterate over the list of commands using a while loop. For every node, we create a new pipe and a new fork, and use the pipes to connect the writing end of the child processess with the reading end of the parent processess. We use ``dup2`` to redirect the input file to the standard input, and similarly in the end redirect to the output file. The child process writes to the ``fd[1]`` instead of the stdout and carefully closes all unnecessary file descriptors. Every child then runs the command from the current node of our list of commands and the pipe sends the output to the parent process. The parent patiently waits till the child process has finished using the pipe and redirects the reading end of the pipe back to the stdin for the next command, closing unused file descriptors.

3) Once the main parent process is done, the contents of the succession of commands should have arrived to the output file. From this point we can call a function I called ``pipex_exit`` to end the program freeing all the allocated memory and closing all the no-longer-used file descriptors.

## Bonus Part

This project has two bonuses: multiple pipe handling, and here_doc stdin

### Multiple Pipes

This bonus was quite simple to do. The algorithm described above will works exactly the same with more parameters, as the only thing that will be different is that the loop will have more nodes from the linked list to iterate over. Other than that, I removed the limitation of having *exactly* four parameters to having *at least* four parameters.

```shell
❯ < file1 cmd1 | cmd2 | cmd3 | cmd4 | cmdn > file2
```

### Here Document

This one was a bit trickier, as it changes the way things will be parsed. This is the new shell command we have to copy:

```shell
❯ cmd << LIMITER | cmd1 >> file
```

Let's break it down again:

* ``cmd``:  first command
* ``<<``:   used to start *here_doc* (short for *here document*) with *LIMITER*
* ``LIMITER``:  limiter word to stop reading from stdin
* ``|``:  pipe to link output of first command to input of the next
* ``cmd1``:   second command
* ``>>``:   redirect to file, creating or appending to it
* ``file``:  output file which may or may not exist

Our program will parse these parameters as follows:

```shell
❯ ./pipex here_doc LIMITER cmd cmd1 file
```
Note: *here_doc* must be written exactly *here_doc* to count as this bonus, otherwise it will be considered the input file

The idea behind the *here_doc* is that you write input with your keyboard saving to stdin until a line matches perfectly with the *LIMITER* word. Here's an example:

```bash
❯ << hello cat
> hi there      
> what's up?
> oh, hello
> hello         
hi there
what's up?
oh, hello
```

To implement this part, some chose to use [get_next_line](https://gitlab.com/madebypixel02/get_next_line) to read one line at a time till the limiter word is found. However, I found it easier to just use a new fork and read one character at a time, looking for the newline character ``\n``. Then I check if the current line matches the limiter and if not I save it all to a buffer, starting all over again. Then I assign this buffer as the infile and I'm good to go :)

Regarding the outfile, it was also pretty straightforward, instead of truncating the outfile with the ``O_TRUNC`` flag, we open the outfile with the ``O_APPEND`` flag, and the other flags remain unchanged

## Installation

* Cloning the repository

```shell
git clone https://github.com/arsenbadalyan/pipex
cd pipex/
make
```

* Usage

```
make			compiles pipex program (mandatory part)
./pipex infile cmd1 cmd2 cmdn outfile // In this case it will behave like bash < infile cmd1 | cmd2 | cmdn > outfile command
./pipex here_doc LIMITER cmd1 cmd2 cmdn outfile // In this case it will work like here_doc in bash

```

## Summary

This project was far more challeging than I thought it would be, and it was quite hard to understand some of the new concepts.

