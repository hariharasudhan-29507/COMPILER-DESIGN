#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function to check if a state is in the accepting set T
bool is_accepting(int cs, const int T[], int T_size) {
    for (int k = 0; k < T_size; k++) {
        if (cs == T[k]) {
            return true;
        }
    }
    return false;
}

// Lexer function
// W: input string
// i: starting index in W
// transition_table: 2D array [state][char_index]
// num_states: number of states
// alphabet: string of valid characters
// T: accepting states
// T_size: number of accepting states
// Returns: lexeme starting at i, or NULL if no valid token
char* dfa_lexer(const char* W, int i,
                 int** transition_table, int num_states,
                 const char* alphabet,
                 const int T[], int T_size) {
    int cs = i;        // current state (we treat state = index in W for simplicity)
    int fp = i;        // forward pointer
    int ns;            // next state
    int len = strlen(W);

    // Move forward while transitions exist
    while (fp < len) {
        // Find index of current character in alphabet
        char ch = W[fp];
        const char* pos = strchr(alphabet, ch);
        if (pos == NULL) {
            // Character not in alphabet -> unknown symbol, stop
            break;
        }
        int char_index = pos - alphabet;

        // Get next state from transition table
        ns = transition_table[cs][char_index];
        if (ns == -1) {
            // No transition for this (state, char) pair
            break;
        }
        cs = ns;
        fp++;
    }

    // Check if current state is accepting
    if (is_accepting(cs, T, T_size) && fp > i) {
        // Extract lexeme from W[i] to W[fp-1]
        int lexeme_len = fp - i;
        char* lexeme = malloc(lexeme_len + 1);
        if (!lexeme) return NULL;
        strncpy(lexeme, W + i, lexeme_len);
        lexeme[lexeme_len] = '\0';
        return lexeme;
    } else {
        return NULL; // No valid lexeme starting at i
    }
}

int main() {
    int num_states, alphabet_size;
    char alphabet[256];
    int** transition_table;
    int T[100];
    int T_size;
    char W[1000];

    // Read alphabet
    printf("Enter the alphabet symbols as a continuous string (e.g., 'ab01'): ");
    scanf("%s", alphabet);
    alphabet_size = strlen(alphabet);

    // Read number of states
    printf("Enter number of states: ");
    scanf("%d", &num_states);

    // Allocate transition table: transition_table[state][char_index]
    transition_table = malloc(num_states * sizeof(int*));
    for (int s = 0; s < num_states; s++) {
        transition_table[s] = malloc(alphabet_size * sizeof(int));
    }

    // Read transition table
    printf("Enter transition table (state x alphabet), use -1 for no transition:\n");
    for (int s = 0; s < num_states; s++) {
        printf("State %d:\n", s);
        for (int c = 0; c < alphabet_size; c++) {
            printf("  on '%c' -> ", alphabet[c]);
            scanf("%d", &transition_table[s][c]);
        }
    }

    // Read accepting states
    printf("Enter number of accepting states: ");
    scanf("%d", &T_size);
    printf("Enter accepting states (space separated): ");
    for (int k = 0; k < T_size; k++) {
        scanf("%d", &T[k]);
    }

    // Read input string
    printf("Enter the string W to analyze: ");
    scanf("%s", W);

    // Run lexer from start (i = 0)
    int i = 0;
    char* lexeme = dfa_lexer(W, i, transition_table, num_states, alphabet, T, T_size);

    if (lexeme) {
        printf("Lexeme starting at position %d: '%s'\n", i, lexeme);
        free(lexeme);
    } else {
        printf("No valid lexeme starting at position %d\n", i);
    }

    // Free memory
    for (int s = 0; s < num_states; s++) {
        free(transition_table[s]);
    }
    free(transition_table);

    return 0;
}
