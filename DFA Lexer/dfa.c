#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function to check if a state is in the accepting set T
bool is_accepting(int cs, const int T[], int T_size) {
    int k;
    for (k = 0; k < T_size; k++) {
        if (cs == T[k]) {
            return true;
        }
    }
    return false;
}

// Lexer function
char* dfa_lexer(const char* W, int i,
                 int** transition_table, const int states[], int num_states,
                 const char* alphabet,
                 const int T[], int T_size) {
    int cs = states[i];        // current state (from state list)
    int fp = i;                // forward pointer (index in W)
    int ns;                    // next state
    int len = strlen(W);
    int char_index;
    const char* pos;
    int s, found;

    // Move forward while transitions exist
    while (fp < len) {
        // Find index of current character in alphabet
        char ch = W[fp];
        pos = strchr(alphabet, ch);
        if (pos == NULL) {
            // Character not in alphabet -> unknown symbol, stop
            break;
        }
        char_index = pos - alphabet;

        // Find current state index in states[] array
        found = -1;
        for (s = 0; s < num_states; s++) {
            if (states[s] == cs) {
                found = s;
                break;
            }
        }
        if (found == -1) {
            // Current state not in state list (should not happen if input is consistent)
            break;
        }

        // Get next state from transition table
        ns = transition_table[found][char_index];
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
    int* states; // array of state labels
    int** transition_table;
    int T[100];
    int T_size;
    char W[1000];
    int s, c, k; // loop variables

    // Read alphabet
    printf("Enter the alphabet symbols as a continuous string (e.g., 'ab01'): ");
    scanf("%s", alphabet);
    alphabet_size = strlen(alphabet);

    // Read number of states
    printf("Enter number of states: ");
    scanf("%d", &num_states);

    // Allocate and read state labels
    states = malloc(num_states * sizeof(int));
    printf("Enter state labels (space separated, e.g., '10 20 30'): ");
    for (s = 0; s < num_states; s++) {
        scanf("%d", &states[s]);
    }

    // Allocate transition table: transition_table[state_index][char_index]
    transition_table = malloc(num_states * sizeof(int*));
    for (s = 0; s < num_states; s++) {
        transition_table[s] = malloc(alphabet_size * sizeof(int));
    }

    // Read transition table
    printf("Enter transition table (state x alphabet), use -1 for no transition:\n");
    for (s = 0; s < num_states; s++) {
        printf("From state %d:\n", states[s]);
        for (c = 0; c < alphabet_size; c++) {
            printf("  on '%c' -> ", alphabet[c]);
            scanf("%d", &transition_table[s][c]);
        }
    }

    // Read accepting states
    printf("Enter number of accepting states: ");
    scanf("%d", &T_size);
    printf("Enter accepting states (space separated): ");
    for (k = 0; k < T_size; k++) {
        scanf("%d", &T[k]);
    }

    // Read input string
    printf("Enter the string W to analyze: ");
    scanf("%s", W);

    // Run lexer from start (i = 0)
    int i = 0;
    char* lexeme = dfa_lexer(W, i, transition_table, states, num_states, alphabet, T, T_size);

    if (lexeme) {
        printf("Lexeme starting at position %d: '%s'\n", i, lexeme);
        free(lexeme);
    } else {
        printf("No valid lexeme starting at position %d\n", i);
    }

    // Free memory
    free(states);
    for (s = 0; s < num_states; s++) {
        free(transition_table[s]);
    }
    free(transition_table);

    return 0;
}
