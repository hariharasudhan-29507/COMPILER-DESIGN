#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function to check if a state is in the accepting set T
bool is_accepting(const char* cs, const char* T[], int T_size) {
    int k;
    for (k = 0; k < T_size; k++) {
        if (strcmp(cs, T[k]) == 0) {
            return true;
        }
    }
    return false;
}

// Lexer function
char* dfa_lexer(const char* W, int i,
                 char*** transition_table, const char* states[], int num_states,
                 const char* alphabet,
                 const char* T[], int T_size) {
    const char* cs = states[i]; // current state label
    int fp = i;                 // forward pointer
    int len = strlen(W);
    int char_index;
    const char* pos;
    int s, found;

    while (fp < len) {
        char ch = W[fp];
        pos = strchr(alphabet, ch);
        if (pos == NULL) {
            break;
        }
        char_index = pos - alphabet;

        found = -1;
        for (s = 0; s < num_states; s++) {
            if (strcmp(states[s], cs) == 0) {
                found = s;
                break;
            }
        }
        if (found == -1) {
            break;
        }

        const char* next_state_label = transition_table[found][char_index];
        if (strcmp(next_state_label, "-1") == 0) {
            break;
        }
        cs = next_state_label;
        fp++;
    }

    if (is_accepting(cs, T, T_size) && fp > i) {
        int lexeme_len = fp - i;
        char* lexeme = malloc(lexeme_len + 1);
        if (!lexeme) return NULL;
        strncpy(lexeme, W + i, lexeme_len);
        lexeme[lexeme_len] = '\0';
        return lexeme;
    } else {
        return NULL;
    }
}

int main() {
    int num_states, alphabet_size;
    char alphabet[256];
    char states[100][10];
    char*** transition_table;
    char* T[100];              // accepting state labels
    int T_size;
    char W[1000];
    int s, c, k;

    printf("Enter the alphabet symbols as a continuous string (e.g., 'ab01'): ");
    fflush(stdout);
    scanf("%s", alphabet);
    alphabet_size = strlen(alphabet);

    printf("Enter number of states: ");
    fflush(stdout);
    scanf("%d", &num_states);

    printf("Enter state labels (space separated, e.g., 'A B C D E'): ");
    fflush(stdout);
    for (s = 0; s < num_states; s++) {
        scanf("%s", states[s]);
    }

    transition_table = malloc(num_states * sizeof(char**));
    for (s = 0; s < num_states; s++) {
        transition_table[s] = malloc(alphabet_size * sizeof(char*));
        for (c = 0; c < alphabet_size; c++) {
            transition_table[s][c] = malloc(10 * sizeof(char));
        }
    }

    printf("Enter transition table (state x alphabet), use '-1' for no transition:\n");
    fflush(stdout);
    for (s = 0; s < num_states; s++) {
        printf("From state %s:\n", states[s]);
        fflush(stdout);
        for (c = 0; c < alphabet_size; c++) {
            printf("  on '%c' -> ", alphabet[c]);
            fflush(stdout);
            scanf("%s", transition_table[s][c]);
        }
    }

    printf("Enter number of accepting states: ");
    fflush(stdout);
    scanf("%d", &T_size);
    printf("Enter accepting state labels (space separated): ");
    fflush(stdout);
    for (k = 0; k < T_size; k++) {
        T[k] = malloc(10 * sizeof(char));
        scanf("%s", T[k]);
    }

    printf("Enter the string W to analyze: ");
    fflush(stdout);
    scanf("%s", W);

    const char* state_ptrs[100];
    for (s = 0; s < num_states; s++) {
        state_ptrs[s] = states[s];
    }

    // Cast T to const char** to match dfa_lexer signature
    int i = 0;
    char* lexeme = dfa_lexer(W, i, transition_table, state_ptrs, num_states, alphabet,
                             (const char**)T, T_size);

    if (lexeme) {
        printf("Lexeme starting at position %d: '%s'\n", i, lexeme);
        free(lexeme);
    } else {
        printf("No valid lexeme starting at position %d\n", i);
    }

    for (s = 0; s < num_states; s++) {
        for (c = 0; c < alphabet_size; c++) {
            free(transition_table[s][c]);
        }
        free(transition_table[s]);
    }
    free(transition_table);
    for (k = 0; k < T_size; k++) {
        free(T[k]);
    }

    return 0;
}
