%{
#include<stdio.h>
#include<string.h>
#include<ctype.h>

char password[100];
%}

%%

^[a-zA-Z][a-zA-Z0-9&@$\-]* {
        int len =strlen(yytext);
        int upper =0,lower=0,digit=0,special=0;
        if(len<8){
                printf("Invalid Password : length should be atleast 8\n");
        }
        if(len>64){
                printf("Invalid Password : length should not exceed 64\n");
        }
        for(int i = 0; i<len ;i++){
                if(isupper(yytext[i])) upper=1 ;
                if(islower(yytext[i])) lower=1 ;
                if(isdigit(yytext[i])) digit=1 ;
                if(yytext[i]=='&'||yytext[i]=='@'||yytext[i]=='$'||yytext[i]=='-') special=1 ;
        }
        if(!upper) printf("invalid no upper case\n");
        if(!lower) printf("invalid no lower case\n");
        if(!digit) printf("invalid no digit\n");
        if(!special) printf("invalid no special\n");
        if(upper&&lower&&special&&digit) printf("valid password\n"); return 0;
}
.|\n {
        printf("Invalid Password : should start with an alphabet and contain only valid character\n");
        return 0;
}
%%

int yywrap(){
        return 1;
}

int main(){
        printf("enter password:");
        yylex();
        return 0;
}
