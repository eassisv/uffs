#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Conta{
    char nome[50];
    char sobrenome[50];
    char cpf;
    char numero_conta;
    char senha[6];
    int limite;
}conta;

int menu_principal(){
    int caso;
    printf("#****************************************#\n");
    printf("#                                        #\n");
    printf("# O que voce deseja fazer?               #\n");
    printf("# Digite 1 para criar uma nova conta.    #\n");
    printf("# Digite 2 para logar na sua conta.      #\n");
    printf("# Digite 0 para sair.                    #\n");
    printf("# "); scanf("%d", &caso); printf("                                      #\n");
    printf("#                                        #\n");
    printf("#****************************************#\n");
    getchar();
    return caso;
}

void criar_conta(FILE *cadastros){
    int res = 2;
    conta dados;
    cadastros = fopen("cadastros.txt", "ab");
    scanf("%[' ' A-Z a-z]s", nome.dados);
    getchar();
    fprintf(cadastros, "%s\n", dados);
    scanf("%[' ' A-Z a-z]s", sobrenome.dados);
    getchar();
    fprintf(cadastros, "%s\n", dados);
    scanf("%[0-9]s", cpf.dados);
    getchar();
    while(res != 0)
        res = verifica_cpf(cpf.dados);
    fprintf(cadastros, "%c", dados);
    fclose(cadastros);
}

int verifica_cpf(int cpf){
    return 0;
    printf("CPF invalido. Digite novamente.\n");
    return 1;
}

void tela_login(){
    int conta_u, res=2;
    char senha;
    printf("#*****************************************#\n");
    printf("#                                         #\n");
    printf("# Digite o numero da sua conta.           #\n");
    printf("# Digite a sua senha.                     #\n");
    printf("# Usuario: "); scanf("%d", &conta_u); printf("                            #\n");
    printf("# Senha: "); scanf("%c", senha); printf("                             #\n");
    printf("#                                         #\n");
    printf("#*****************************************#\n");
    getchar();
    while(res != 0)
        res = verifica_conta_senha(conta, senha);
        printf("O numero da conta e a senha nao correspondem.\n Por favor digite novamente\n");
}

int main(void){
    int caso;
    FILE *cadastros;
    tela_login();
    caso = menu_principal();
    switch(caso){
        case 0: break;

        case 1: criar_conta(cadastros);

        case 2: acessar_conta();

        default:
    }
    return 0;
}
