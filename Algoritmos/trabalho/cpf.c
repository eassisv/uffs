#include <string.h>

int verificaCpf(char cpf[]){
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
		if (dig != cpf[9] - '0') {
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