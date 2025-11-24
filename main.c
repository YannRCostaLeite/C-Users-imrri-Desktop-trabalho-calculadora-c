#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

#include "expressao.h"

int main() {
    Expressao exp;

    printf("Digite a expressao em forma pos-fixa (ex: 3 4 + 2 *):\n");
    fgets(exp.posFixa, sizeof(exp.posFixa), stdin);


    size_t len = strlen(exp.posFixa);
    if (len > 0 && exp.posFixa[len - 1] == '\n') {
        exp.posFixa[len - 1] = '\0';
    }

    char *infixa = getFormaInFixa(exp.posFixa);
    if (infixa == NULL) {
        printf("Erro ao converter para forma infixa!\n");
        return 1;
    }


    exp.Valor = getValorPosFixa(exp.posFixa);

   
    strcpy(exp.inFixa, infixa);

   
    printf("\n=== RESULTADO ===\n");
    printf("Pos-fixa: %s\n", exp.posFixa);
    printf("In-fixa: %s\n", exp.inFixa);
    printf("Valor: %.2f\n", exp.Valor);

    free(infixa);

    return 0;
}
