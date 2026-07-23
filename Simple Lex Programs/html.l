%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
%}

%%

"<a"[ ]+"href"[ ]*"="[ ]*"\""[^\"]*"\"" {
        char *start = strstr(yytext, "href");
        if(start){
                start = strstr(start, "\"") + 1;
                /* FIX: Changed double quotes to single quotes for character matching */
                char *end = strchr(start , '"');
                if(end){
                        *end = '\0';
                        printf("Found : %s\n", start);
                }
        }
}

\n      ;
.       ;

%%

int main(){
        FILE *fp;
        fp = fopen("first.html", "r");
        if(fp == NULL){
                printf("File not found\n");
                return 0;
        }
        yyin = fp;
        yylex();
        fclose(fp);
        return 0;
}

int yywrap(){
        return 1;
}
