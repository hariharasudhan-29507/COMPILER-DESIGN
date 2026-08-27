%{
#include <stdio.h>
#include <stdlib.h>

FILE *yyin;
int last_was_operand = 0;
%}

%s START

%%

<INITIAL>"for" { printf("<KEYWORD, %s>\n", yytext); last_was_operand = 0; BEGIN(START); }
"int"|"float"|"double"|"char"|"boolean" { printf("<DATATYPE, %s>\n", yytext); last_was_operand = 0; }
"true"|"false" { printf("<BOOLEAN, %s>\n", yytext); last_was_operand = 1; }
"=="|"!="|"<="|">="|"<"|">" { printf("<RELATIONAL_OPERATOR, %s>\n", yytext); last_was_operand = 0; }

"++"|"--" {
    if (last_was_operand) {
        printf("<POST_INCREMENT_OPERATOR, %s>\n", yytext);
    } else {
        printf("<PRE_INCREMENT_OPERATOR, %s>\n", yytext);
    }
    last_was_operand = 1;
}

"&&"|"||"|"!" { printf("<LOGICAL_OPERATOR, %s>\n", yytext); last_was_operand = 0; }

"+"|"-" {
    if (last_was_operand) {
        printf("<BINARY_OPERATOR, %s>\n", yytext);
        last_was_operand = 0;
    } else {
        printf("<UNARY_OPERATOR, %s>\n", yytext);
        last_was_operand = 0;
    }
}

"*"|"%"|"=" { printf("<BINARY_OPERATOR, %s>\n", yytext); last_was_operand = 0; }

[a-zA-Z_][a-zA-Z0-9_]* { printf("<IDENTIFIER, %s>\n", yytext); last_was_operand = 1; }
[0-9]+(\.[0-9]+)? { printf("<NUMBER, %s>\n", yytext); last_was_operand = 1; }

"("|"{"|"[" { printf("<PUNCTUATION, %s>\n", yytext); last_was_operand = 0; }
")"|"}"|"]" { printf("<PUNCTUATION, %s>\n", yytext); last_was_operand = 1; }
":"|";"|"," { printf("<SEPARATOR,%s>\n", yytext); last_was_operand = 0; }

"\"" { printf("<DOUBLE_QUOTE, %s>\n", yytext); last_was_operand = 0; }
"'" { printf("<SINGLE_QUOTE, %s>\n", yytext); last_was_operand = 0; }
"\\" { printf("<BACKSLASH, %s>\n", yytext); last_was_operand = 0; }
"/" { printf("<BINARY_OPERATOR, %s>\n", yytext); last_was_operand = 0; }

[ \t\n]+ { }
. { printf("<UNKNOWN, %s>\n", yytext); }

%%

int yywrap()
{
    return 1;
}

int main()
{
    yyin = fopen("Input.java", "r");
    if (!yyin)
    {
        printf("Error: Could not open Input.java!\n");
        return 1;
    }
    printf("Reading and tokenizing Input.java...\n\n");
    yylex();
    fclose(yyin);
    return 0;
}
