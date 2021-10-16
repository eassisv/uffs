#include <stdio.h>
#include <string.h>
#include <ctype.h>

void upVogais(char s[]){
	int i;
	for(i = 0; i < strlen(s) - 1; i++)
		if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
			s[i] = toupper(s[i]);
}

int main(void){
	char s[50];

	fgets(s, 50, stdin);
	upVogais(s);
	printf("%s", s);

	return 0;
}