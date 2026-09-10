# get_next_line

*This project has been created as part of the 42 curriculum by juho.*


## Description

`get_next_line` is a function that reads and returns, one call at a time, a single line from a file descriptor — without loading the entire file into memory at once. Each call picks up exactly where the previous one left off, so calling it repeatedly on the same file descriptor walks through the file line by line.

The goal of the project is to understand how to manage data that **persists between separate function calls** in C, and how to work with `read()` in fixed-size chunks that don't naturally align with line boundaries — a single `read()` can return part of a line, an entire line, several lines at once, or nothing at all.

This implementation includes the **bonus part**: it correctly handles reading from **multiple file descriptors at the same time** (e.g. alternating reads between two open files), using a single static variable shared across all of them, rather than one static variable per call site.

## Instructions

### Compilation

`get_next_line` is typically compiled directly alongside a test file, with the chunk size controlled at compile time via the `BUFFER_SIZE` macro:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c your_test_main.c -o gnl_test
```

`BUFFER_SIZE` can be set to any positive value to test how the function behaves with tiny reads (e.g. `1`) versus large reads (e.g. `9999`) — correct output shouldn't depend on the chunk size used.

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd;
    char  *line;

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

Each returned line includes the trailing `\n` if one was present in the file; the last line of a file without a final newline is still returned correctly, and `get_next_line` returns `NULL` once there's nothing left to read (or on error).

## Resources

- `man 2 read` — how `read()` fills a buffer and what its return value means (bytes read, `0` for EOF, `-1` for error)
- `man 2 open` / `man 2 close` — working with file descriptors
- 42 Norminette documentation — coding style constraints followed throughout the project
- Classic 42 community explainers on `get_next_line`'s static-variable persistence trick (widely discussed across 42 forums/wikis — worth reading a couple for the "why," not for copying implementations)

**AI usage:** Claude (Anthropic) was used as a learning aid — specifically to talk through why a `static` variable is needed to retain leftover, unprocessed data between separate calls to the function, and to reason through the tradeoffs of different ways to track a separate leftover buffer per file descriptor for the bonus part. All code was written, tested, and debugged independently; AI was not used to generate any of the submitted source files.

<!-- Be specific and honest here about what you actually used it for — staff will ask. -->

## Algorithm Justification

The core challenge is that `read()` has no concept of "lines" — it just returns however many bytes happen to be available, up to `BUFFER_SIZE`, with no guarantee that a chunk ends neatly at a `\n`. A single `read()` might return half a line, three and a half lines, or an empty result at end-of-file. But `get_next_line` has to hand back **exactly one clean line per call**, so anything read past the end of the current line has to be **saved somewhere** and reused on the *next* call, instead of being discarded.

That's what makes a `static` variable the right tool here: unlike a normal local variable, a `static` variable keeps its value between separate calls to the function instead of resetting each time. It acts as the function's "memory" of whatever text was already read but not yet handed back to the caller.

**Per call, the flow is:**
1. If there's already a `\n` sitting in the leftover buffer from last time, skip straight to extracting the line — no need to read anything new.
2. Otherwise, call `read()` in a loop, each time appending the newly read chunk onto the leftover buffer, until either a `\n` shows up in it, or `read()` returns `0` (EOF) or `-1` (error).
3. Split the leftover buffer at the first `\n`: the part up to and including it becomes the line returned to the caller; whatever remains after it becomes the new leftover buffer, saved back into `static` storage for the next call.

**For the bonus (multiple file descriptors):** a single `static` variable can only hold one value, so reading two file descriptors alternately with a naive single-fd design would corrupt both — each call would clobber the other fd's leftover data. The fix is to make that one `static` variable hold **a leftover buffer per file descriptor** (indexed by the fd number) rather than a single flat string, so each fd's unread data is tracked independently and reading from one fd never disturbs the state of another.

<!-- Adjust this paragraph to describe your actual per-fd storage: an array indexed by fd (simple, bounded by a max fd count) vs. a linked list of (fd, leftover) pairs (handles arbitrarily large fd numbers, more complex to manage/free). -->
