#include <stdio.h>
#include <string.h>
#include "cadastro.h"

int main(void){
	int opcao, verificador;
	double gasto;
	char senha[20], usuario[20];
	conta user;
	
	telaLogin(usuario, senha);
	
	//Menu para usuario root
	if(!strcmp(usuario, "root"))
		if(strcmp(senha, SENHA_ROOT)){
			printf("Senha incorreta\n");
			return 0;
		}
		else{
			opcao = menuRoot();
			while(opcao){
				switch(opcao){
				case 1:
					printf("Digite o nome do cliente: ");
					scanf("%[a-z A-Z ' ']s", user.nome);
					getchar();
					printf("Digite o sobrenome do cliente: ");
					scanf("%[a-z A-Z]s", user.snome);
					getchar();
					printf("Digite o CPF do cliente: ");
					scanf("%[0-9]s", user.cpf);
					getchar();
					if(!verificaCpf(user.cpf)){
						printf("CPF invalido\n");
						break;
					}
					printf("Digite a senha com 6 digitos: ");
					scanf("%[a-z A-Z 0-9]s", user.senha);
					getchar();
					while(strlen(user.senha) != 6){
						printf("A deve ter 6 digitos:\nDigite novamente:");
						scanf("%[a-z A-Z 0-9]s", user.senha);
						getchar();
					}
					verificador = cadastraConta(user);
					if(verificador == -1)
						printf("Ocorreu um erro ao realizar o cadastro\n");
					else
					printf("Cadastro realizado com sucesso\nn* da conta %d\n", verificador);
					break;
				case 2:
					verificador = limpaGastos();
					if(!verificador)
						printf("Conta inexistente ou ocorreu um erro ao abrir o arquivo\n");
					else
						printf("Gastos deletados com sucesso\n");
					break;
				case 3:
					verificador = aprovaCredito();
					if(!verificador)
						printf("Nao ha solicitacoes para atender\n");
					if(verificador == -1)
						printf("Ocorreu um erro ao abrir o arquivo, tente novamente mais tarde\n");
					if(verificador == 1)
						printf("Todas solicitacoes foram atendidas\n");
					break;
				case 4:
					verificador = excluiConta();
					if(!verificador)
						printf("Conta inexistente\n");
					if(verificador == -1)
						printf("Ocorreu um erro ao abrir o arquivo, tente novamente mais tarde\n");
					if(verificador == 1)
						printf("Conta deletada com sucesso\n");
					break;
				default:
					printf("Opcao invalida\n");
				}
				printf("\n");
				opcao = menuRoot();
			}
		}
	
	//Menu para usuarios normais
	else{
		if(!verificaSenha(&user, usuario, senha)){
			printf("Usuario ou senha incorretos.\n");
			return 0;
		}else if(verificaSenha(&user, usuario, senha) == -1){
			printf("Falha ao verficar os dados, tente novamente mais tarde.\n");
			return 0;
		}
		else{			
			opcao = menuUsuario(user.nome);
			while(opcao){
				if(!verificaGasto(user.numConta, &user.gasto)){
					printf("Ocorreu um erro ao abrir a conta, tente novamente mais tarde");
					return 0;
				}
				switch(opcao){
				case 1:
					printf("Seu saldo e: %.2lf\n", user.saldo - user.gasto);
					break;
				case 2:
					if(!mostraGasto(user.numConta))
						printf("Ocorreu um erro, tente novamente mais tarde\n");
						break;
				case 3:
					if(user.gasto > 0.00)
						printf("Voce precisa efetuar o pagamento primeiramente\n");
					else{
						verificador = solicitaAumento(user);
						if(verificador == -1) printf("Ocorreu um erro, tente novamente mais tarde\n");
						if(verificador == 1) printf("Solicitacao realizada com sucesso\n");
					}
					break;
				case 4:
					printf("Digite o quanto voce quer gastar: ");
					scanf("%lf", &gasto);
					if((user.saldo - gasto) < 0)
						printf("Voce nao tem saldo suficiente, efetue o pagamento\n");
					else{
						verificador = registraGasto(gasto, user.numConta);
						if(!verificador)
							printf("Ocorreu um erro, tente novamente mais tarde\n");
						else
							printf("Gasto registrado com sucesso\n");
					}
					break;
				default:
					printf("Opcao invalida!\n");
				}
				printf("\n");
				opcao = menuUsuario(user.nome);
			}
		}
	}
	
	return 0;
}
