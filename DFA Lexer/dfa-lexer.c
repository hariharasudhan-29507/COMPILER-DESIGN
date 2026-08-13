#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_accepting(const char* cs, const char* T[], int T_size) {
    int k;
    for (k = 0; k < T_size; k++) {
        if (strcmp(cs, T[k]) == 0) {
            return true;
        }
    }
    return false;
}

char* dfa_lexer(const char* W, int i,
                 char*** transition_table, const char* states[], int num_states,
                 const char* alphabet,
                 const char* T[], int T_size) {
    const char* cs = states[i];
    int fp = i;
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
    char* T[100];
    int T_size;
    char W[1000];
    int s, c, k;
    int num_strings;
    int str_idx;

    printf("Enter the input symbols : (a , b / 0, 1) ");
    fflush(stdout);
    scanf("%s", alphabet);
    alphabet_size = strlen(alphabet);

    printf("Enter number of states: ");
    fflush(stdout);
    scanf("%d", &num_states);

    printf("Enter state (A , B , C ...): ");
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

    printf("\nEnter the transition table (%d rows x %d columns'%s'):\n", num_states, alphabet_size, alphabet);
    printf("Use '-1' for no transition.\n Enter data:\n\n");
    fflush(stdout);

    for (s = 0; s < num_states; s++) {
        for (c = 0; c < alphabet_size; c++) {
            scanf("%s", transition_table[s][c]);
        }
    }

    printf("\nEnter number of accepting states: ");
    fflush(stdout);
    scanf("%d", &T_size);
    printf("Enter accepting state: ");
    fflush(stdout);
    for (k = 0; k < T_size; k++) {
        T[k] = malloc(10 * sizeof(char));
        scanf("%s", T[k]);
    }

    const char* state_ptrs[100];
    for (s = 0; s < num_states; s++) {
        state_ptrs[s] = states[s];
    }

    printf("\nEnter number of strings: ");
    fflush(stdout);
    scanf("%d", &num_strings);

    for (str_idx = 0; str_idx < num_strings; str_idx++) {
        printf("Enter string: ");
        fflush(stdout);
        scanf("%s", W);

        char* lexeme = dfa_lexer(W, 0, transition_table, state_ptrs, num_states, alphabet,
                                 (const char**)T, T_size);

        if (lexeme) {
            printf("Lexeme: %s accepted\n", lexeme);
            free(lexeme);
        } else {
            printf("Lexeme not accepted\n");
        }
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
