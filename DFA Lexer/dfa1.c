#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_accepting(int cs, const int T[], int T_size) {
    int k;
    for (k = 0; k < T_size; k++) {
        if (cs == T[k]) {
            return true;
        }
    }
    return false;
}

char* dfa_lexer(const char* W, int i,
                 int** transition_table, const int states[], int num_states,
                 const char* alphabet,
                 const int T[], int T_size) {
    int cs = states[i];        // current state
    int fp = i;                // forward pointer
    int ns;
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
            if (states[s] == cs) {
                found = s;
                break;
            }
        }
        if (found == -1) {
            break;
        }

        ns = transition_table[found][char_index];
        if (ns == -1) {
            break;
        }
        cs = ns;
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
    int* states;
    int** transition_table;
    int T[100];
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

    states = malloc(num_states * sizeof(int));
    printf("Enter state labels as integers (space separated, e.g., '1 2 3 4 5'): ");
    fflush(stdout);
    for (s = 0; s < num_states; s++) {
        scanf("%d", &states[s]);
    }

    transition_table = malloc(num_states * sizeof(int*));
    for (s = 0; s < num_states; s++) {
        transition_table[s] = malloc(alphabet_size * sizeof(int));
    }

    printf("Enter transition table (state x alphabet), use -1 for no transition:\n");
    fflush(stdout);
    for (s = 0; s < num_states; s++) {
        printf("From state %d:\n", states[s]);
        fflush(stdout);
        for (c = 0; c < alphabet_size; c++) {
            printf("  on '%c' -> ", alphabet[c]);
            fflush(stdout);
            scanf("%d", &transition_table[s][c]);
        }
    }

    printf("Enter number of accepting states: ");
    fflush(stdout);
    scanf("%d", &T_size);
    printf("Enter accepting states (space separated): ");
    fflush(stdout);
    for (k = 0; k < T_size; k++) {
        scanf("%d", &T[k]);
    }

    printf("Enter the string W to analyze: ");
    fflush(stdout);
    scanf("%s", W);

    int i = 0;
    char* lexeme = dfa_lexer(W, i, transition_table, states, num_states, alphabet, T, T_size);

    if (lexeme) {
        printf("Lexeme starting at position %d: '%s'\n", i, lexeme);
        free(lexeme);
    } else {
        printf("No valid lexeme starting at position %d\n", i);
    }

    free(states);
    for (s = 0; s < num_states; s++) {
        free(transition_table[s]);
    }
    free(transition_table);

    return 0;
}
