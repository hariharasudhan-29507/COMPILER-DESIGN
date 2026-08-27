%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;

int yylex(void);
void yyerror(const char *s);
%}

%token FOR INT FLOAT DOUBLE CHAR
%token NUMBER IDENTIFIER
%token RELATIONAL INCREMENT
%token ASSIGN OPERATOR
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON
%token INVALID

%%

program:
    for_loop
    ;

for_loop:
    FOR LPAREN initialization SEMICOLON condition SEMICOLON increment RPAREN
    LBRACE statements RBRACE
    ;

initialization:
    type IDENTIFIER ASSIGN expression
    | IDENTIFIER ASSIGN expression
    ;

type:
    INT
    | FLOAT
    | DOUBLE
    | CHAR
    ;

condition:
    expression RELATIONAL expression
    ;

increment:
    IDENTIFIER INCREMENT
    | INCREMENT IDENTIFIER
    | IDENTIFIER ASSIGN expression
    ;

expression:
    IDENTIFIER
    | NUMBER
    | expression OPERATOR expression
    ;

statements:
    statement
    | statements statement
    ;

statement:
    IDENTIFIER ASSIGN expression SEMICOLON
    | IDENTIFIER INCREMENT SEMICOLON
    | IDENTIFIER INCREMENT
    ;

%%

int main()
{
    yyin = fopen("input.java", "r");

    if (!yyin)
    {
        printf("Error in opening file\n");
        return 1;
    }

    if (yyparse() == 0)
        printf("Valid Java for loop\n");
    else
        printf("Invalid Java for loop\n");

    fclose(yyin);

    return 0;
}

void yyerror(const char *s)
{
}
