#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SENHA_ROOT "123456"

typedef struct Conta{
	char cpf[20], nome[50], snome[50];
	int numConta;
	double saldo, gasto;
	char senha[15];
}conta;

//Cabecalho de funcoes

int verificaCpf(char cpf[]);
int geraCodigo(int semente);
void geraDigito(int *codigo);
int cadastraConta(conta usuario);
void telaLogin(char usuario[], char senha[]);
int menuRoot();
int verificaSenha(conta *user, char usuario[], char senha[]);
int menuUsuario(char nome[]);
int solicitaAumento(conta user);
void geraEndereco(char endereco[], int num);
int registraGasto(double gasto, int numConta);
int verificaGasto(int numConta, double *gasto);
int mostraGasto(int numConta);
int limpaGastos();
int aprovaCredito();
int excluiConta();

//Funcoes implementadas

int excluiConta(){
	/*Essa funcao exclui a conta do cliente*/
	FILE *fKey, *fCad, *fCod;
	int numConta, opcao, numContaAnt;
	double solSaldo;
	conta user;
	char endereco[20] = {"gastos/"};
		
	printf("Digite o numero da conta para ser excluida\n");
	scanf("%d", &numConta);
	getchar();
	geraEndereco(endereco, numConta);
	
	
	fKey = fopen("senhas.txt", "r+");
	fCad = fopen("cadastros.txt", "r+");
	fCod = fopen("codigos.txt", "r+");
	if(fKey == NULL || fCad == NULL || fCod == NULL) return -1;
	
	numContaAnt = 0;
	while(fscanf(fCod, "%d", &user.numConta) != EOF){
		printf("%d\n", user.numConta);
		if(user.numConta == numConta){
			strcpy(user.nome, "00000");
			fwrite(&user.nome, sizeof(user.nome) + sizeof(user.snome) +
					sizeof(user.cpf) + sizeof(user.saldo), 1, fCad);
			fprintf(fKey,"%s\n", user.senha);
			rewind(fCod);
			if(numContaAnt)
				while(fscanf(fCod, "%d", &user.numConta))
					if(user.numConta != numContaAnt)
						break;
			user.numConta = 0;
			fwrite(&user.numConta, sizeof(int), 1, fCod);
			remove(endereco);	
			fclose(fCod);
			fclose(fKey);
			fclose(fCad);
			return 1;
		}
		numContaAnt = user.numConta;
		fscanf(fCad, "%s %s %s %lf", user.nome, user.snome, user.cpf, &user.saldo);
		fscanf(fKey, "%s", user.senha);
	}
	
	return 0;
}

int aprovaCredito(){
	/*Essa funcao aprova as solicitacoes de credito pendentes*/
	FILE *fSol, *fCad, *fCod;
	int numConta, opcao;
	double solSaldo;
	conta user;
	char endereco[20] = {"gastos/"};
	
	fSol = fopen("solicitacoes.txt", "r+");
	fCad = fopen("cadastros.txt", "r+");
	fCod = fopen("codigos.txt", "r+");
	if(fSol == NULL || fCad == NULL || fCod == NULL) return -1;
	if(fscanf(fSol, "%d %lf", &numConta, &solSaldo) == EOF) return 0;
	
	printf("Digite 1 para aceitar solicitacao e 0 para recusar\n");
	rewind(fSol);
	while(fscanf(fSol, "%d %lf", &numConta, &solSaldo) != EOF){
		printf("Conta: %d, solicita aumento para %.2lf\n", numConta, solSaldo);
		scanf("%d", &opcao);
		getchar();
		if(!opcao) continue;
		rewind(fCad);
		rewind(fCod);
		while(fscanf(fCod, "%d", &user.numConta) != EOF){
			fscanf(fCad, "%s %s %s ", user.nome, user.snome, user.cpf);
			if(numConta == user.numConta){
				fprintf(fCad, "%.2lf\n", solSaldo);
				break;
			}
			fscanf(fCad, "%lf", &user.saldo);
		}
	}
	fclose(fSol);
	fclose(fCod);
	fclose(fCad);
	fSol = fopen("solicitacoes.txt", "w");
	if(fSol == NULL) printf("Ocorreu um erro ao limpar as solicitacoes\n");
	fclose(fSol);
	
	return 1;
}

int limpaGastos(){
	/*Essa funcao limpa o arquivo de gastos do cliente*/
	int numConta;
	char endereco[50] = {"gastos/"};
	FILE *fGastos;
	
	printf("Digite o numero da conta\n");
	scanf("%d", &numConta);
	
	geraEndereco(endereco, numConta);
	
	fGastos = fopen(endereco, "r");
	if(fGastos == NULL) return 0;
	fclose(fGastos);
	
	fGastos = fopen(endereco, "w");
	if(fGastos == NULL) return 0;
	
	fclose(fGastos);
	
	return 1;
	
}

int mostraGasto(int numConta){
	/*Essa funcao vai imprimir na tela os gastos do cliente
	 *por categorias a funcao retorna 0 caso tenha ocorrido
	 *erro ao abrir o arquivo e 1 caso de certo*/
	FILE *fGastos;
	char endereco[20] = {"gastos/"};
	int i, categoria;	
	double gastos, gastosTotal;
	
	geraEndereco(endereco, numConta);
	
	fGastos = fopen(endereco, "r");
	if(fGastos == NULL) return 0;
	
	for(i = 1, gastosTotal = 0.0; i < 10; i++){
		rewind(fGastos);
		while(fscanf(fGastos, "%d %lf", &categoria, &gastos) != EOF){
			if(categoria == i)
				gastosTotal += gastos;
		}
		switch(i){
			case 1:
				printf("Gastos com farmacia: %.2lf\n", gastosTotal);
				break;
			case 2:
				printf("Gastos com supermercado: %.2lf\n", gastosTotal);
				break;
			case 3:
				printf("Gastos com roupas: %.2lf\n", gastosTotal);
				break;
			case 4:
				printf("Gastos com lazer: %.2lf\n", gastosTotal);
				break;
			case 5:
				printf("Gastos com livraria: %.2lf\n", gastosTotal);
				break;
			case 6:
				printf("Gastos com esporte: %.2lf\n", gastosTotal);
				break;
			case 7:
				printf("Gastos com moveis: %.2lf\n", gastosTotal);
				break;
			case 8:
				printf("Gastos com carro: %.2lf\n", gastosTotal);
				break;
			case 9:
				printf("Gastos com educacao: %.2lf\n", gastosTotal);
				break;
		}
		gastosTotal = 0.0;
	}
	fclose(fGastos);
	return 1;
}

int verificaGasto(int numConta, double *gasto){
	/*Essa funcao calcula o gasto total do cliente e retorna 0
	 *caso tenha problema para abrir o arquivo e 1 caso tenha
	 *conseguido ler os gastos*/
	FILE *fGastos;
	int categoria;
	double gastoParcial = 0.0;
	char endereco[50] = {"gastos/"};
	
	geraEndereco(endereco, numConta);
	
	fGastos = fopen(endereco, "r");
	if(fGastos == NULL) return 0;
	
	*gasto = 0.0;
	while(fscanf(fGastos, "%d %lf", &categoria, &gastoParcial) != EOF){
		*gasto += gastoParcial;
	}
	fclose(fGastos);
	return 1;	
}

int registraGasto(double gasto, int numConta){
	/*Essa funcao registra o gasto que o cliente fez e
	 *retorna 0 caso tenha ocorrido erro ao abrir o arquivo
	 *e retorna 1 caso de tudo certo */
	int cod_compra;
	FILE *fGastos;
	char endereco[50] = {"gastos/"};
	
	printf("%d\n", numConta);
	geraEndereco(endereco, 	numConta);
	
	fGastos = fopen(endereco, "a");
	
	if(fGastos == NULL) return 0;
	
	printf("Digite o codigo da compra:\n1 = Farmacia\n2 = Supermecado\n");
	printf("3 = Roupas\n4 = Lazer\n5 = Livraria\n6 = Esporte\n7 = Moveis\n8 = Carro\n9 = Educacao\n");
	scanf("%d", &cod_compra);
	getchar();
	fprintf(fGastos, "%d %.2lf\n", cod_compra, gasto);
	fclose(fGastos);
	return 1;
}

int solicitaAumento(conta user){
	/*A funcao registra o pedido de aumento de credito
	 *e retorna -1 caso tenha erro ao abrir o arquivo
	 *retorna 0 caso o cliente digite um valor menor e queira desistir do aumento
	 *retorna 1 caso solicitacao tenha sido registrada*/
	double nSaldo;
	int numConta;
	FILE *fSol;
	
	fSol = fopen("solicitacoes.txt", "r");
	if(fSol == NULL) return -1;
	
	while(fscanf(fSol, "%d %lf", &numConta, &nSaldo) != EOF){
		if(numConta == user.numConta){
			printf("Voce ja possui uma solicitacao pendente, por favor aguarde\n");
			return 0;
		}
	}
	fclose(fSol);
	
	fSol = fopen("solicitacoes.txt", "a");
	if(fSol == NULL) return -1;
		
	printf("Seu saldo atual e de: %.lf\n", user.saldo);
	printf("Qual saldo gostaria de ter: ");
	scanf("%lf", &nSaldo);
	getchar();
	while(nSaldo <= user.saldo){
		printf("Este saldo e menor ou igual ao atual\n digite outro saldo ou 0 para sair. ");
		scanf("%lf", &nSaldo);
		getchar();
		if(!nSaldo)
			return 0;
	}
	fprintf(fSol, "%d %.2lf\n", user.numConta, nSaldo);
	fclose(fSol);
	return 1;	
}

int verificaSenha(conta *user, char usuario[], char senha[]){
	//Verifica se o usuario existe e se a senha esta correta
	FILE *fKey, *fCod, *fCad;
	conta tmpUser;
	char tmpSenha[20]; 
	int codigo, tmpUsuario;
	fCad = fopen("cadastros.txt", "r");
	fCod = fopen("codigos.txt", "r");
	fKey = fopen("senhas.txt", "r");
	if(fCad == NULL || fCod == NULL || fKey == NULL)
		return -1;
	codigo = atoi(usuario);
	while(fscanf(fCod, "%d", &tmpUsuario) != EOF){
		fscanf(fKey, "%s", tmpSenha);
		fscanf(fCad, "%s %s %s %lf", tmpUser.nome, tmpUser.snome, tmpUser.cpf, &tmpUser.saldo);
		if(codigo == tmpUsuario && !strcmp(tmpSenha, senha)){
			strcpy(tmpUser.senha, senha);
			tmpUser.numConta = codigo;
			*user = tmpUser;
			return 1;
		}
	}
	return 0;
}

int menuRoot(){
    int opcao;
    printf("******************************************\n");
    printf("*                                        *\n");
    printf("* O que voce deseja fazer?               *\n");
    printf("* Digite 1 para criar uma nova conta.    *\n");
    printf("* Digite 2 Limpar os gastos da conta.    *\n");
    printf("* Digite 3 para aprovacao de credito.    *\n");
    printf("* Digite 4 para excluir uma conta.       *\n");
    printf("* Digite 0 para sair.                    *\n");
    printf("*                                        *\n");
    printf("******************************************\n");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}

int menuUsuario(char nome[]){
    int opcao;
    printf("******************************************\n");
    printf("  Bem vindo %s\n", nome);
    printf("*                                        *\n");
    printf("* O que voce deseja fazer?               *\n");
    printf("* Digite 1 para consultar o saldo.       *\n");
    printf("* Digite 2 para ver os gastos.           *\n");
    printf("* Digite 3 para solicitar aumento.       *\n");
    printf("* Digite 4 para informar gasto.          *\n");
    printf("* Digite 0 para sair.                    *\n");
    printf("*                                        *\n");
    printf("******************************************\n");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}

void telaLogin(char usuario[], char senha[]){
	printf("*****************************\n");
	printf("*           LOGIN           *\n");
	printf("*****************************\n");
	printf("Usuario.: ");
	scanf("%s", usuario); getchar();
	printf("Senha...: ");
	scanf("%s", senha); getchar();
}

int verificaCpf(char cpf[]){
	/*Verifica se o CPF e valido, retorna 0 caso seja invalido
	e retorna 1 caso seja valido*/
	int peso, dig, i;
	//Verifica o tamanho do CPF digitado
	if (strlen(cpf) > 11 || strlen(cpf) < 11){
		return 0;
	}
	else{
		//Verifica o primeiro digito do CPF
		for (i = dig = 0, peso = 10; i < strlen(cpf) - 2; i++)
			dig += (cpf[i] - '0' ) * peso--;
		if (dig % 11 < 2) 
			dig = 0;
		else
			dig = 11 - (dig % 11);
		if (dig != cpf[9] - '0')
			return 0;
		//Verifica o segundo digito do CPF
		for (i = dig = 0, peso = 11; i < strlen(cpf) - 1; i++)
			dig += (cpf[i] - '0') * peso--;
		if (dig % 11 < 2) 
			dig = 0;
		else
			dig = 11 - (dig % 11);
		if (dig != cpf[10] - '0')
			return 0;
	}	
	return 1;
}

int geraCodigo(int semente){
	/*Gera um codigo unico apartir de uma semente*/
	srand(semente);
	return (rand() % 9999);
}

void geraEndereco(char endereco[], int num){
	/*Essa funcao gera um endereco para o arquivo de gastos do cliente
	 *apartir do numero de sua conta*/
	char s[8] = {};
	int i, x;
	for(i = 0, x = 10000; i < 5; i++){
		s[i] = '0' + (num / x);
		if((num / x) > 0) num -= (num / x) * x;
		x /= 10;
	}
	strcat(endereco, s);
	strcat(endereco, ".txt");
}

void geraDigito(int *codigo){
	/*Gera o codigo verificador da conta*/
	int i, peso, x = 1000, tmpCod = 0;
	for(i = 0, peso = 9; i < 4;i++){
		tmpCod = (*codigo / x) * peso--;
	}
	tmpCod %= 11;
	if(tmpCod > 9) *codigo *= 10;
	else *codigo = *codigo * 10 + tmpCod;
}

int cadastraConta(conta user){
	/*A funcao cadastra o usuario e retorna o numero da conta
	caso tenha algum erro para cadastrar o usuario retorna -1 */
	
	//Criando e inicializando as variavéis
	int codigo = 0, i = 0, semente = 0, tmpCod;
	FILE *fCad, *fCod, *fKey, *fGastos;
	char enderecoGastos[30] = {"gastos/"};
	
	//Abrindo o arquivo para leitura
	fCod = fopen("codigos.txt", "r");
	if(fCod == NULL) return -1;
	
	//Gerando código único para conta a conta do cliente
	for(i = 0; i < 11; i++)
		semente += (user.cpf[i] - '0');
	
	codigo = geraCodigo(semente);
	if(!codigo) return -1;
	
	while(fscanf(fCod, "%d", &tmpCod) != EOF){
		if((tmpCod / 10) == codigo){
			codigo = geraCodigo(tmpCod);
	    rewind(fCod);
		}
	}
	geraDigito(&codigo);
	if(tmpCod == codigo) return -1;
	fclose(fCod);
	
	//Gravando dados da nova conta no arquivo
	
	geraEndereco(enderecoGastos, codigo);
	
	fCad = fopen("cadastros.txt", "a");
	fCod = fopen("codigos.txt", "a");
	fKey = fopen("senhas.txt", "a");
	fGastos = fopen(enderecoGastos, "w");
	if(fCad == NULL || fCod == NULL || fKey == NULL || fGastos == NULL)
		return -1;
	fprintf(fCad, "%s %s %s %.2lf\n", user.nome, user.snome, user.cpf, 600.00);
	fprintf(fCod, "%d\n", codigo);		
	fprintf(fKey, "%s\n", user.senha);
	fclose(fCad);
	fclose(fGastos);
	fclose(fCod);
	fclose(fKey);
		
	return codigo;
}
