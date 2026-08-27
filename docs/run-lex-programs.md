# Running Compiler Design Programs

This guide provides instructions for building and running the Lex (`.l`), YACC (`.y`), and C programs in this repository.

## Prerequisites

Ensure you have `flex`, `bison` (or `yacc`), and `gcc` installed.

On Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y flex bison gcc
```

---

## 1. Simple Lex Programs

Programs located in `Simple Lex Programs/` take input either from stdin or from files in `Assets/`.

### Example: Running `department.l`

```bash
flex "Simple Lex Programs/department.l"
gcc lex.yy.c -o department
./department
```

*Note: `department.l` expects `student.txt` to be present in the working directory or execution directory.*

### Example: Running `html.l`

```bash
flex "Simple Lex Programs/html.l"
gcc lex.yy.c -o html_parser
./html_parser
```

---

## 2. DFA Lexer (C Program)

Located in `DFA Lexer/dfa-lexer.c`.

### Build and Run:

```bash
gcc "DFA Lexer/dfa-lexer.c" -o dfa_lexer
./dfa_lexer
```

---

## 3. Parsing with Lex and YACC/Bison

The `Parsing - Programs/` and `Parsing - YAAC/` directories contain complementary Lex and YACC files for parsing tasks (e.g., Java `for` loop parser).

### Build and Run (`for.l` + `for.y`):

```bash
bison -d "Parsing - YAAC/for.y"
flex "Parsing - Programs/for.l"
gcc for.tab.c lex.yy.c -o for_parser
./for_parser
```

*Note: `for.y` reads from `input.java`. Ensure an `input.java` file exists in the directory where the binary is executed.*
