#include<stdio.h>

#include<parser.h>
#include<string.h>

#include<readline/readline.h>

#define MAXLINE 666

int main(void){
    char *exp;
    int error;
    double val;
    while (1) {
        exp=readline("Digite uma expressao: ");
        if (!strcmp(exp, "exit")){
            printf("Saindo da melhor calculadora ;D\n");
            break;
        }
        val = parser(exp, &error);
        if(error == ERR_SUCESS){
            printf("Expressao: %f.\n", val);
        }else{
            printf("Entrada invalida.\n");
        }
	free(exp);
    }
    free(exp);
    return 0;
}
