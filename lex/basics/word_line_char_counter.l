%{
#include <stdio.h>

int words = 0;
int lines = 0;
int chars = 0;
%}

%%
\n          { lines++; chars++; }
[ \t\r]+    { chars += yyleng; }
[^ \t\r\n]+ { words++; chars += yyleng; }
%%

int main(void) {
    yylex();
    printf("Lines: %d\nWords: %d\nCharacters: %d\n", lines, words, chars);
    return 0;
}

int yywrap(void) {
    return 1;
}
