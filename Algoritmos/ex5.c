#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
	int i, leng;
	char s[112] = {}, aux[112] = {};

	printf("Digite a palavra: ");
	scanf("%s", s);
	for (i = 0, leng = strlen(s) - 1; leng >= 0; i++, leng--){
		s[i] = tolower(s[i]);
		aux[leng] = s[i];
	}
	printf("%s\n", (!strcmp(aux, s))? "E palindromo" : "Nao e palindromo");
		
	return 0;
}


