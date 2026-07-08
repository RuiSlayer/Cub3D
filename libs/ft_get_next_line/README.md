# get_next_line

> A function that reads a file descriptor line by line — part of the 42 School curriculum.

## Overview

`get_next_line` returns one line at a time from a file descriptor each time it is called, including the terminating `\n` character (except at end of file). It works correctly with files, stdin, and any valid file descriptor, handling **multiple successive calls** to read through an entire file.

The key challenge is managing a **static buffer** that preserves leftover data between calls — bytes read beyond the newline are saved and used on the next call without re-reading from the fd.

***

## Function Prototype

```c
char *get_next_line(int fd);
```

| Parameter | Description |
|---|---|
| `fd` | File descriptor to read from (file, stdin, pipe, etc.) |

**Return values:**

| Return | Condition |
|---|---|
| A line string (with `\n`) | Successful read |
| A line string (without `\n`) | Last line of file with no trailing newline |
| `NULL` | End of file reached or error |

The returned string is heap-allocated — the caller is responsible for freeing it.

***

## BUFFER_SIZE

Reading is done in chunks of `BUFFER_SIZE` bytes, defined at compile time:

```bash
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

The function must work correctly for any positive `BUFFER_SIZE` value — from `1` to very large numbers. If not defined, a default is used.

***

## File Structure

| File | Description |
|---|---|
| `get_next_line.c` | Core function — reads from `fd`, manages the static buffer, extracts lines |
| `get_next_line_utils.c` | Helper functions — `get_buff_length`, `get_line_length`, `resize_buff`, `has_newline`, `create_line` |
| `get_next_line.h` | Header — prototypes, `BUFFER_SIZE` fallback define, includes |

***

## Internal Functions

| Function | Description |
|---|---|
| `get_next_line(int fd)` | Main function — reads from `fd` and returns the next line |
| `get_buff_length(char *buff)` | Returns the current length of the static buffer |
| `get_line_length(char *line)` | Returns the length of the next line (up to and including `\n`) |
| `has_newline(char *line)` | Checks whether the buffer contains a `\n` character |
| `create_line(char *line, char *buff)` | Builds and returns the next line from the buffer |
| `resize_buff(char *buff)` | Trims the buffer after a line has been extracted, keeping leftover bytes |

***

## Compilation

```bash
# With default BUFFER_SIZE
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -o gnl

# With custom BUFFER_SIZE
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=64 get_next_line.c get_next_line_utils.c -o gnl
```

***

## Usage

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

***

## How It Works

1. **Read** up to `BUFFER_SIZE` bytes from `fd` into a temporary buffer
2. **Append** the newly read bytes to a `static` leftover string (persisted between calls)
3. **Check** for a `\n` using `has_newline` — if not found, keep reading
4. **Measure** the line length with `get_line_length` and build the return string with `create_line`
5. **Trim** the static buffer via `resize_buff`, keeping bytes after the `\n` for the next call
6. Return `NULL` when `read` returns `0` and the buffer is empty (EOF)

***

## Key Concepts

- **Static variable** — a `static char *` inside `get_next_line` persists its value across calls, storing bytes read beyond the last newline
- **`BUFFER_SIZE`** — controls how many bytes are read per `read()` call; the function's correctness must be independent of its value
- **Heap allocation** — each returned line is a newly allocated string; the caller must `free()` it after use
- **No global variables** — only one static variable is permitted

***

*Made with ❤️ at 42 School.*
