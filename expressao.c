#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "expressao.h"


typedef struct {
    char itens[512][512];
    int topo;
} PilhaStr;

void pushStr(PilhaStr *p, const char *v) {
    if (p->topo < 511) {
        strcpy(p->itens[++p->topo], v);
    }
}

char *popStr(PilhaStr *p) {
    if (p->topo >= 0) return p->itens[p->topo--];
    return NULL;
}


typedef struct {
    float itens[512];
    int topo;
} PilhaFloat;

void pushFloat(PilhaFloat *p, float v) {
    p->itens[++p->topo] = v;
}

float popFloat(PilhaFloat *p) {
    return p->itens[p->topo--];
}


char *getFormaInFixa(char *Str) {
    PilhaStr pilha;
    pilha.topo = -1;

    char token[128];
    int i = 0;

    while (sscanf(Str + i, "%s", token) == 1) {
        i += strlen(token) + 1;

        
        int ehNumero = 1;
        for (int j = 0; token[j]; j++) {
            if (!isdigit(token[j]) && token[j] != '.') {
                ehNumero = 0;
                break;
            }
        }

        if (ehNumero) {
            pushStr(&pilha, token);
        } else {
            
            char *b = popStr(&pilha);
            char *a = popStr(&pilha);

            if (!a || !b) return NULL; 

            char novo[512];
            sprintf(novo, "(%s%s%s)", a, token, b);
            pushStr(&pilha, novo);
        }
    }

    if (pilha.topo != 0) return NULL;

    // Remover parênteses externos
    char *resultado = malloc(512);
    strcpy(resultado, pilha.itens[pilha.topo]);

    int len = strlen(resultado);
    if (resultado[0] == '(' && resultado[len - 1] == ')') {
        resultado[len - 1] = '\0';
        memmove(resultado, resultado + 1, len - 1);
    }

    return resultado;
}


float getValorPosFixa(char *StrPosFixa) {
    PilhaFloat pilha;
    pilha.topo = -1;

    char token[128];
    int i = 0;

    while (sscanf(StrPosFixa + i, "%s", token) == 1) {
        i += strlen(token) + 1;

        if (isdigit(token[0])) {
            pushFloat(&pilha, atof(token));
        } else {
            float b = popFloat(&pilha);
            float a = popFloat(&pilha);

            switch (token[0]) {
                case '+': pushFloat(&pilha, a + b); break;
                case '-': pushFloat(&pilha, a - b); break;
                case '*': pushFloat(&pilha, a * b); break;
                case '/': pushFloat(&pilha, a / b); break;
                default: return 0;
            }
        }
    }

    return popFloat(&pilha);
}
