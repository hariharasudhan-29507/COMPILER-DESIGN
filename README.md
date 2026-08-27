# COMPILER-DESIGN

Repository for storing compiler design programs including Lex (`.l`), YACC/Bison (`.y`), and C implementations with a clean structure and clear build/run instructions.

## Repository Structure

```text
COMPILER-DESIGN/
├── Assets/
│   ├── first.html
│   └── student.txt
├── DFA Lexer/
│   └── dfa-lexer.c
├── Parsing - Programs/
│   └── for.l
├── Parsing - YAAC/
│   └── for.y
├── Simple Lex Programs/
│   ├── department.l
│   ├── html.l
│   ├── iswas.l
│   └── password.l
└── docs/
    └── run-lex-programs.md
```

## Overview of Directories

- **`Assets/`**: Input files used by various programs (e.g., sample HTML and text files).
- **`DFA Lexer/`**: C implementation of a Deterministic Finite Automaton (DFA) based lexical analyzer.
- **`Parsing - Programs/`**: Lexical analyzer specifications (`.l`) written to work in conjunction with parsers.
- **`Parsing - YAAC/`**: YACC/Bison syntax parser specifications (`.y`) for grammar analysis (e.g., Java `for` loop syntax).
- **`Simple Lex Programs/`**: Standalone Lex specifications for tasks like counting occurrences, matching patterns, and validating inputs.
- **`docs/`**: Additional documentation and setup guides.

## Quick Start / How to Run

Refer to the detailed run guide in [`docs/run-lex-programs.md`](docs/run-lex-programs.md).
