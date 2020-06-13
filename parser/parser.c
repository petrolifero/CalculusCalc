#include <parser.h>

static int number(char* s, int* error, int* advancedChar){
    int i = 0, aux = 0;
    if ((s[i] == '-') || (s[i] == '+')){i++;}
    
    if (s[i] < '0' || s[i] > '9'){
        *advancedChar = 0;
        *error = ERR_NAN;
        return 0;
    }
    *error = ERR_SUCESS;
    
    while (s[i] != '\0' && !(s[i] < '0' || s[i] > '9')){
        aux = aux*10 + (s[i] - '0');
        i++;
    }
    *advancedChar = i;
    if (s[0] == '-') {
        return aux * -1;
    }
    return aux;
}

static int term (char* s, int* error, int* advancedChar) {
    int auxResp;
    int resp = number(s, error, advancedChar);
    while (ERR_SUCESS == *error
    && (s[*advancedChar] == '+' || s[*advancedChar] == '-')
    && (s[*advancedChar + 1] != '-' && s[*advancedChar + 1] != '+')) {
        int auxAdvancedChar;
        auxResp = number(s + *advancedChar + 1, error, &auxAdvancedChar);
        if (ERR_SUCESS == *error) {
            if (s[*advancedChar] == '+'){
                resp = resp + auxResp;
            }else{
                resp = resp - auxResp;
            }
            *advancedChar = *advancedChar + auxAdvancedChar + 1;
        }
    }
    return resp;
}

int parser(char* s, int* error){
    int advancedChar = 0;
    int resp = term(s, error, &advancedChar);
    if(*error == ERR_SUCESS && s[advancedChar] != '\0') {
        *error = ERR_PARTIALEXPRESSION;
    }
    return resp;
}