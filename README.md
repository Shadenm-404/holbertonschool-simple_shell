# Simple Shell Project

This repository implements a small UNIX command interpreter in C (GNU89).
It supports interactive and non-interactive modes, executes external programs
via `fork()`/`execve()`, and provides a minimal set of built-ins.

---

## Description

The shell behaves similarly to `/bin/sh` for the features implemented:
- Prompt + REPL loop (interactive) and stdin-driven execution (non-interactive)
- PATH search for commands without `/`
- Built-ins: `exit [n]`, `env`
- Error messages formatted with program name and line number
- Betty-style compliant; ≤ 5 functions per file

---

## Tasks Overview

**Task 0 — README, man, AUTHORS**
- Provide this `README.md`, `man_1_simple_shell`, and an `AUTHORS` file listing contributors as:

**Task 1 — Betty would be proud**
- All files pass Betty checks; no file contains more than 5 functions.

**Task 2 — Simple Shell 0.1**
- Display a prompt, read a single word command, execute it via `fork()`/`execve()`.
- Loop until EOF or `exit`.

**Task 3 — Simple Shell 0.2**
- Search the command in `PATH` (if it has no `/`).
- If not found, print:

**Task 4 — Simple Shell 0.3**
- Handle EOF (Ctrl+D) cleanly without crashing or looping.

**Task 5 — Simple Shell 0.4**
- Implement `exit [n]`.
- If `n` is not a valid number:
Do not exit; return status `2`.

**Task 6 — Simple Shell 1.0**
- Implement `env` to print the current environment (using `environ`).

**Task 13 — setenv, unsetenv**
- Implement two new built-in commands:
- **`setenv VARIABLE VALUE`**
  - Adds a new environment variable or modifies an existing one.
  - Prints an error to `stderr` on failure.
- **`unsetenv VARIABLE`**
  - Removes an environment variable from the environment list.
  - Prints an error to `stderr` on failure.

---

## Build

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

Start the shell and enter commands at the prompt:

```bash
$ ./hsh
$ /bin/ls
file1.c  file2.c  README.md
$ exit
```

### Non‑Interactive Mode

Feed commands via a pipe or file:

```bash
echo "/bin/ls" | ./hsh
file1.c  file2.c  README.md
```
---

## Example Errors

hsh: 3: foo: not found
exit
hsh: 7: exit: Illegal number: abc

---

## Repository
git clone https://github.com/Shadenm-404/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell

---

## Authors

Sondoas Alrubaish & Shaden Alalwani
