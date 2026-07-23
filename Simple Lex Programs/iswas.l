%{
#include<stdio.h>
#include<stdlib.h>
int count=0;
%}
%%
[\t\n ]+is[\t\n ]+  {
        printf("was");
        count++;
}
[0-9]+ {
        printf("%d",atoi(yytext)+10);
}

\n ECHO;
. ECHO;

%%

int main(){
        printf("Enter text: ");
        yylex();

        printf("number of occurences of \"is\" = %d\n", count);
        return 0 ;
}

int yywrap(){
        return 1;
}
