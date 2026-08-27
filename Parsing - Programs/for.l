%{
#include <stdio.h>
#include <stdlib.h>

FILE *yyin;
%}

%option caseless

%%

"for"
        { printf("<KEYWORD, %s>\n", yytext); }

"int"|"float"|"double"|"char"|"boolean"
        { printf("<DATATYPE, %s>\n", yytext); }

"true"|"false"
        { printf("<BOOLEAN, %s>\n", yytext); }

"=="|"!="|"<="|">="|"<"|">"
        { printf("<RELATIONAL_OPERATOR, %s>\n", yytext); }

"++"|"--"
        { printf("<INCREMENT_OPERATOR, %s>\n", yytext); }

"="|"+"|"-"|"*"|"/"|"%"
        { printf("<OPERATOR, %s>\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*
        { printf("<IDENTIFIER, %s>\n", yytext); }

[0-9]+(\.[0-9]+)?
        { printf("<NUMBER, %s>\n", yytext); }

"("|")"|"{"|"}"|";"|","
        { printf("<PUNCTUATION, %s>\n", yytext); }

[ \t\n]+
        { /* Ignore whitespace */ }

.
        { printf("<UNKNOWN, %s>\n", yytext); }

%%

int yywrap()
{
    return 1;
}

int main()
{
    yyin = fopen("input.txt", "r");

    if (!yyin)
    {
        printf("Error: Could not open input.txt!\n");
        return 1;
    }

    printf("Reading and tokenizing input.txt...\n\n");

    yylex();

    fclose(yyin);

    return 0;
}
