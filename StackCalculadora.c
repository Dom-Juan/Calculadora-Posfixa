#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define maxSize 102
#define ERROR -999999

typedef struct stackChar{
    char postfix[maxSize];
    int top;
}stChar;

typedef struct stackInt{
    int stack[maxSize];
    int top;
}stInt;

// Inicia a estrutura da pilha de inteiros
stInt *initStackInt(stInt *stackInt){
    stackInt = (stInt*)malloc(sizeof(stInt));
    stackInt->top = 0;


    printf("top(int): %d\n", stackInt->top);

    return stackInt;
}

// Inicia a estrutura com a "pilha" de caracteres.
stChar *initStackChar(stChar *stackChar){
    stackChar = (stChar*)malloc(sizeof(stChar));
    stackChar->top = 0;


    printf("top(char): %d\n", stackChar->top);

    return stackChar;
}

// Empurra um elemento para a pilha.
void push(int number, stInt *stackInt){
    if(stackInt->top >= maxSize-1)
        printf("\nStack over flow!!!\n\n");
    else {
        stackInt->stack[stackInt->top] = number;
        printf("Pushing: %d\ntop: %d\n", stackInt->stack[stackInt->top], stackInt->top);
        stackInt->top = stackInt->top + 1;

    }
}

// Retira um elemento da pilha.
int pop(stInt *stackInt){
    int number;
    if(stackInt->top < 0)
        printf("\nStack under flow!!!\n\n");
    else {
        stackInt->top = stackInt->top - 1;
        number = stackInt->stack[stackInt->top];
        printf("Poping:%d\ntop:%d\n\n", stackInt->stack[stackInt->top],stackInt->top);

        return number;
    }
    return ERROR;
}

// Retorna true ou false se for digito.
bool ehDigito(char c){
    if( c >= '0' && c <= '9')
        return true;
    else
        return false;
}

// Converte um char numero para um numero int.
int charParaDigito(char c){
    if(ehDigito(c) == true)
        return c - '0';
    else return 0;
}

// Verifica se o char realmente eh um numero.
bool ehNumero(char *c){
    while(*c){
        if(ehDigito(*c) == false)
            return false;
        c++;
    }
    return true;
}

// Avalia a expressao digitada, retornando o valor da conta prefixa.
void avaliarExpressao(stChar *stackChar, stInt *stackInt){
    char ch;
    int result, number1, number2, i;

    if(stackChar->top == 0) {
        printf("Posfixo nao foi digitado!!\n");
        return;
    } else {
        for (i = 0; stackChar->postfix[i] != '\0'; i++) { // Loop aonde as operacoes ocorrem.
            printf("======================iteracao%d==============================\n",i);
            ch = stackChar->postfix[i];
            printf("char: %c\n",ch);
            if(ehDigito(ch) == true){
                int auxNumber = charParaDigito(ch);
                push(auxNumber,stackInt);
            } else if( ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                number1 = pop(stackInt);
                number2 = pop(stackInt);
                char aux = ch;
                if(ehNumero(&aux) && (ch == '/' && number1 == 0)) { // nao permite a divisao por zero
                    printf("Dividindo por zero, erro!\nSaindo do programa...\n");
                    exit(1);
                } else {
                    printf("Realizando operacao...\n");
                    switch (ch) {
                        case '+':
                            result = number2 + number1;
                            printf("Resultado: %d\n",result);
                            break;
                        case '-':
                            result = number2 - number1;
                            printf("Resultado: %d\n",result);
                            break;
                        case '*':
                            result = number2 * number1;
                            printf("Resultado: %d\n",result);
                            break;
                        case '/':
                            result = number2 / number1;
                            printf("Resultado: %d\n",result);
                            break;
                        default:
                            printf(">Erro na interpretacao da expressao!!!\n\n");
                            break;
                    }
                    push(result,stackInt); // retorna o valor pra stack depois de fazer as operacoes.
                }
            }
            printf("============================================================\n");
        }

        printf("\n O resultado da avaliacao da expressao %s eh: %d\n",stackChar->postfix, pop(stackInt));
    }
}

int main() {
    stInt  *stackInt = NULL;
    stChar *stackChar = NULL;

    // Iniciando as strings.
    stackInt = initStackInt(stackInt);
    stackChar = initStackChar(stackChar);

    // Colocando os valores na estrutura.
    strcpy(stackChar->postfix,"12-45+*");
    stackChar->top = strlen(stackChar->postfix);

    // Mostrando o posfixo digitado.
    printf("\nPosfixo: %s\n",stackChar->postfix);

    // Realiza a expressao.
    avaliarExpressao(stackChar,stackInt);

    return 0;
}
