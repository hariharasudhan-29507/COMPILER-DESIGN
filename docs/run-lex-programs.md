# Running Lex Programs

This repository stores compiler design exercises as Lex (`.l`) files.

## Prerequisites

- `flex`
- `gcc`

On Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y flex gcc
```

## Build and Run

From the repository root:

```bash
flex lex/basics/word_line_char_counter.l
gcc lex.yy.c -o word_counter
./word_counter < input.txt
```

## Expected Output

The sample program prints:

- Number of lines
- Number of words
- Number of characters
