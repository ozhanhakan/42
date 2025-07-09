# get\_next\_line

This project is part of the 42 curriculum. It aims to implement a function `get_next_line()` that reads a line from a file descriptor, handling multiple calls and multiple descriptors simultaneously (bonus).

---

## 📌 Project Objectives

- Implement `get_next_line(int fd)` that returns the next line from a file descriptor.
- Each call returns the next line, including the terminating `\n` if it exists.
- The function must work with any `BUFFER_SIZE > 0`.
- Must handle multiple file descriptors (bonus part).
- No memory leaks or crashes.

---

## 📁 File Overview

| File                          | Purpose                                    |
| ----------------------------- | ------------------------------------------ |
| `get_next_line_bonus.c`       | Core logic for reading and returning lines |
| `get_next_line_bonus.h`       | Header file, BUFFER\_SIZE definition       |
| `get_next_line_utils_bonus.c` | Helper functions (string, memory ops)      |

---

## ⚙️ Usage

### 🧪 Compile Example:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line_bonus.c get_next_line_utils_bonus.c \
    main.c -o gnl_test
```

### 📥 Sample `main.c`:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int fd = open("sample.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## ✅ Behavior

- Returns a line ending with `\n` if present.
- Returns the last line even without a trailing `\n`.
- Returns `NULL` when EOF is reached or on error.
- Handles invalid `fd` gracefully (e.g., `get_next_line(-1)` returns `NULL`).
- Works with different `BUFFER_SIZE` values.

---

## 🛠 Edge Cases Covered

- Empty file → returns `NULL` immediately.
- File ending without newline → line still returned.
- Multiple descriptors → independent line tracking.
- `BUFFER_SIZE = 1`, `2`, `10`, `9999` etc. tested.

---

## 🔐 Static Management

Uses:

```c
static char *stash[1024];
```

This allows tracking up to 1024 simultaneous `fd`s.

⚠️ You must check `fd >= 0 && fd < 1024` to avoid buffer overflow.

---

## 🔍 Memory Safety

- All allocations are freed properly.
- `ft_free()` helper used to safely free and nullify pointers.
- Can be tested with `valgrind`:

```bash
valgrind --leak-check=full ./gnl_test
```

---

## 📦 Bonus

✅ Supports multiple file descriptors simultaneously. ✅ Single static variable used for stash.

---

## 🧪 Testing Tips

Test your code with files like:

- Single line with and without newline.
- Multiple lines.
- Very long lines (2k+).
- Very short lines (1-char).
- Empty lines or empty file.
- Reading from `stdin` (fd = 0).

---

## 🧑‍💻 Author

- Developed by: `hozhan@student.42kocaeli.com.tr`
- For the `42 Cursus` GNL Project

---

## 📚 License

This project is educational and intended for peer learning within the 42 Network.

