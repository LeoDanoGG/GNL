*This project has been created as part of the 42 curriculum by legomez.*

# get_next_line

## Description

`get_next_line` is a C function that reads a file descriptor and returns its
content **one line at a time**. Each call returns the next line, including the
trailing `\n` when there is one, and returns `NULL` when there is nothing left
to read or when an error occurs.

The goal of the project is to learn about **static variables**, **dynamic
memory management** and **file descriptor reading** with `read`, while keeping
the code memory-safe (no leaks) and independent from the value of
`BUFFER_SIZE`.

Allowed external functions: `read`, `malloc`, `free`.

### Files

| File                   | Content                                             |
| ---------------------- | --------------------------------------------------- |
| `get_next_line.c`      | `get_next_line` and its main helper functions       |
| `get_next_line_utils.c`| `ft_strlen`, `ft_strchr`, `ft_strjoin`, `ft_substr` |
| `get_next_line.h`      | Prototypes, includes and the default `BUFFER_SIZE`  |

## Algorithm: explanation and justification

### Data structure

The whole algorithm revolves around `static char *stack`. A static
variable keeps its value between calls, so it acts as a buffer of
**data that has already been read from the file descriptor but not yet
returned to the caller**. This is what makes it possible to read in chunks of
`BUFFER_SIZE` bytes, which almost never match the length of a line, without
losing the extra bytes that were read.

### Flow of a call

1. **Initialize.** If the stack is `NULL` (first call, or after the previous
   one emptied it), it is created as an empty string `""`. This way the rest
   of the code can always assume the stack is a valid string.
2. **Fill (`fill_stack`).** While the stack has no `\n`, `take_bytes` reads up
   to `BUFFER_SIZE` bytes into a temporary buffer, `ft_strjoin` appends it to
   the stack, and both the old stack and the temporary buffer are freed. The
   loop ends when a `\n` appears in the stack, or when `read` returns 0 (EOF)
   or -1 (error).
3. **Check.** If the stack is `NULL` or empty after filling, there is nothing
   left to return: the stack is freed, set to `NULL`, and the function
   returns `NULL`.
4. **Extract (`build_line`).** The line is the substring from the start of
   the stack up to and including the first `\n`, or up to the end of the
   stack if there is none (last line of a file without a trailing newline).
5. **Save (`save_stack`).** The stack is replaced by a new string with
   everything after the `\n`, and the old one is freed. If there is no `\n`,
   the stack is freed and set to `NULL`.

### Example

File content `hello\nworld\n` with `BUFFER_SIZE=4`:

| Call | Stack before | Reads                 | Stack after reads | Returned   | Stack after |
| ---- | ------------ | --------------------- | ----------------- | ---------- | ----------- |
| 1    | `""`         | `hell`, `o\nwo`       | `hello\nwo`       | `hello\n`  | `wo`        |
| 2    | `wo`         | `rld\n`               | `world\n`         | `world\n`  | `""`        |
| 3    | `""`         | `read` returns 0      | `""`              | `NULL`     | `NULL`      |

### Responsibilities of each function

| Function       | Responsibility                                              |
| -------------- | ----------------------------------------------------------- |
| `take_bytes`   | One `read` into a freshly allocated buffer; `NULL` on EOF/error |
| `fill_stack`   | Accumulates reads in the stack until a `\n` or EOF          |
| `build_line`   | Extracts the line to return from the stack                  |
| `save_stack`   | Keeps only the leftover after the returned line             |
| `get_next_line`| Validates arguments, initializes the stack and coordinates the rest |

### Memory management

- Every temporary buffer is freed right after being appended to the stack.
- Every replaced stack is freed before the new one is stored.
- The stack is freed and set to `NULL` as soon as it becomes empty, so after
  reading a file to the end no memory remains allocated.
- If an allocation fails at any point, the stack is released and the function
  returns `NULL`.

### Justification

- **Reading in chunks.** Reading `BUFFER_SIZE` bytes per `read` reduces the
  number of system calls compared to reading byte by byte, and the algorithm
  stays correct for any `BUFFER_SIZE`, from 1 to very large values.
- **Static stack for leftovers.** A single read can contain the end of one
  line and the start of the next. Since file offsets cannot be rewound
  (`lseek` is not allowed, and it would not work on `stdin` or pipes), the
  extra bytes have to be kept between calls. A static variable does exactly
  that without needing any extra parameter.
- **One string instead of a linked list.** Keeping the stack as a single
  contiguous string makes searching for `\n` and extracting the line a
  matter of simple string functions, with few allocations to track and
  therefore fewer places where memory can leak. It also fits the project's
  constraints (at most 5 functions per file and 25 lines per function)
  without needing many extra helpers.
- **Separation of responsibilities.** Reading, filling, extracting and saving
  are independent functions, which makes each one easier to understand, test
  and debug.

### Trade-offs and limitations

- **Cost of concatenation.** `ft_strjoin` copies the whole stack every time a
  chunk is appended. For a line of length `n` and a buffer of size `B`, there
  are about `n / B` reads and each copies up to `n` bytes, so the cost is
  `O(n² / B)`. This is negligible for normal inputs, but becomes noticeable
  with `BUFFER_SIZE=1` and extremely long lines. A linked list of chunks
  would copy each byte only once (`O(n)`), at the price of more allocations
  and more code.
- **Read errors.** `take_bytes` returns `NULL` both for EOF and for a `read`
  error, so an error in the middle of a file is handled like an EOF: the
  data already in the stack is still returned before the function reports
  `NULL`.
- **Single file descriptor.** The mandatory part uses one static stack, so
  interleaving reads from different file descriptors would mix their data.

## Instructions

### Compilation

The project can be compiled with or without the `BUFFER_SIZE` flag. If it is
not defined, the default value from `get_next_line.h` is used.

```sh
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

### Usage

Include the header and call `get_next_line` repeatedly until it returns
`NULL`. The caller is responsible for freeing each returned line.

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open( <file> , O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

### Behavior

- Works with regular files and with standard input (`fd = 0`).
- Each returned line ends with `\n`, except the last one if the file does not
  end with a newline.
- Returns `NULL` when there is nothing left to read, on an invalid file
  descriptor or if `BUFFER_SIZE <= 0`.

### Testing

Test with several buffer sizes (for example 1, 42 and 10000000) and with edge
cases: empty file, file without a trailing newline, only newlines, very long
lines and an invalid file descriptor. Check memory with:

```sh
valgrind --leak-check=full ./a.out
```

## Resources

- [`read(2)`](https://man7.org/linux/man-pages/man2/read.2.html) manual page for the behavior of `read` and its return values.
- [`malloc(3)`](https://man7.org/linux/man-pages/man3/malloc.3.html) manual page for dynamic memory allocation.
- [`free(3)`](https://man7.org/linux/man-pages/man3/free.3.html) manual page for dynamic memory freedom.
- [Google](https://google.com) for general searches.

### Use of AI

AI tools were used as a support for understanding and reviewing the code, not
to replace the development of the project:

[**Claude**](https://claude.ai/new) → Review of the logic, detection of bugs (NULL handling, string termination in helper functions, line-count limits) and test suggestions.

*All the code was reviewed, understood and tested by me*.