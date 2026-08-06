#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Example DFA definition
// States: 0, 1, 2, ...
// Alphabet: 'a', 'b', ...
// Accepting states: stored in T[]
// Transition function: move(state, char) -> next_state or -1

// Example move function for a simple DFA recognizing words like "ab*"
// You must replace this with your actual DFA transition table.
int move(int state, char ch) {
    switch (state) {
        case 0:
            if (ch == 'a') return 1;
            break;
        case 1:
            if (ch == 'b') return 1;
            break;
    }
    return -1; // no transition for this (state, char) pair
}

// Lexer function
// W: input string
// i: starting state
// T: set of accepting states
// T_size: number of accepting states
// Returns: lexeme starting at position i, or NULL if no valid token
char* dfa_lexer(const char* W, int i, const int T[], int T_size) {
    int cs = i;        // current state
    int fp = i;        // forward pointer
    int ns;            // next state
    int len = strlen(W);

    // Move forward while transitions exist
    while (fp < len) {
        ns = move(cs, W[fp]);
        if (ns == -1) {
            // No transition: stop here
            break;
        }
        cs = ns;
        fp++;
    }

    // Check if current state is accepting
    bool accepting = false;
    for (int k = 0; k < T_size; k++) {
        if (cs == T[k]) {
            accepting = true;
            break;
        }
    }

    // If not accepting, no valid lexeme starting at i
    if (!accepting || fp == i) {
        return NULL;
    }

    // Extract lexeme from W[i] to W[fp-1]
    int lexeme_len = fp - i;
    char* lexeme = malloc(lexeme_len + 1);
    if (!lexeme) return NULL;
    strncpy(lexeme, W + i, lexeme_len);
    lexeme[lexeme_len] = '\0';

    return lexeme;
}

// Example usage
int main() {
    const char* W = "abbbcab";
    int i = 0; // start from beginning

    // Accepting states for the example DFA
    int T[] = {1};
    int T_size = sizeof(T) / sizeof(T[0]);

    char* lexeme = dfa_lexer(W, i, T, T_size);
    if (lexeme) {
        printf("Lexeme: '%s'\n", lexeme);
        free(lexeme);
    } else {
        printf("No valid lexeme starting at position %d\n", i);
    }

    return 0;
}
