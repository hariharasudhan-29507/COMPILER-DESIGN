%{
#include<stdio.h>
int count =0;
%}

%%

[0-9][0-9](BCS|BEC|BIT)[0-9][0-9][0-9] {
        printf("roll numbers: %s\n",yytext);
        count++;
}
\n
.

%%

int main(){
        FILE *fp;
        fp = fopen("student.txt","r");
        if(fp==NULL){
                printf("file not found\n");
                return 0;
        }
        yyin=fp;
        yylex();
        printf("\nTotal student records:%d \n",count);
        fclose(fp);
        return 0;
}

int yywrap(){
        return 1;
}
