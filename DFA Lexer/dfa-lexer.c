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

char* dfa_lexer(const char* W, int start_pos, int start_state_idx,
                char*** transition_table, const char* states[], int num_states,
                const char* alphabet,
                const char* T[], int T_size,
                int* out_fp, int* out_accepted, int* out_cause) {
    const char* cs = states[start_state_idx];
    int fp = start_pos;
    int len = strlen(W);
    int char_index;
    const char* pos;
    int s, found;

    *out_cause = 0;

    while (fp < len) {
        char ch = W[fp];
        pos = strchr(alphabet, ch);
        if (pos == NULL) {
            *out_cause = 1;
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
            *out_cause = 2;
            break;
        }
        cs = next_state_label;
        fp++;
    }

    *out_fp = fp;

    if (is_accepting(cs, T, T_size) && fp > start_pos) {
        *out_accepted = 1;
        int lexeme_len = fp - start_pos;
        char* lexeme = malloc(lexeme_len + 1);
        if (!lexeme) return NULL;
        strncpy(lexeme, W + start_pos, lexeme_len);
        lexeme[lexeme_len] = '\0';
        return lexeme;
    } else {
        *out_accepted = 0;
        if (fp > start_pos) {
            int lexeme_len = fp - start_pos;
            char* lexeme = malloc(lexeme_len + 1);
            if (!lexeme) return NULL;
            strncpy(lexeme, W + start_pos, lexeme_len);
            lexeme[lexeme_len] = '\0';
            return lexeme;
        } else {
            return NULL;
        }
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

    printf("\nEnter the transition table (%d rows x %d columns '%s'):\n", num_states, alphabet_size, alphabet);
    printf("Use '-1' for no transition.\nEnter data:\n\n");
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

        int len = strlen(W);
        int pos = 0;

        while (pos < len) {
            int stopped_pos;
            int accepted_flag;
            int cause;
            char* lexeme = dfa_lexer(W, pos, 0,
                                     transition_table, state_ptrs, num_states, alphabet,
                                     (const char**)T, T_size,
                                     &stopped_pos, &accepted_flag, &cause);

            if (accepted_flag) {
                printf("Lexeme: %s accepted\n", lexeme);
                pos = stopped_pos;
                free(lexeme);
            } else if (lexeme) {
                if (cause == 1) {
                    printf("Lexeme not accepted, unknown symbol '%c' at position %d, lexeme %s\n",
                           W[stopped_pos], stopped_pos + 1, lexeme);
                } else if (cause == 2) {
                    printf("Lexeme not accepted, no transition at position %d, lexeme %s\n",
                           stopped_pos + 1, lexeme);
                } else {
                    printf("Lexeme not accepted, stopped at position %d, lexeme %s\n",
                           stopped_pos + 1, lexeme);
                }
                pos = stopped_pos;
                free(lexeme);
            } else {
                if (cause == 1) {
                    printf("Lexeme not accepted, unknown symbol '%c' at position %d\n",
                           W[stopped_pos], stopped_pos + 1);
                    pos = stopped_pos + 1;
                } else if (cause == 2) {
                    printf("Lexeme not accepted, no transition at position %d\n", stopped_pos + 1);
                    pos = stopped_pos + 1;
                } else {
                    printf("Lexeme not accepted, no characters consumed\n");
                    pos++;
                }
            }
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
