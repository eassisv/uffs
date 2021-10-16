#include <stdio.h>

int main(){
	char s[56];

	fgets(s, 56, stdin);
	//scanf("%s", s);
	printf("..%d..\n", s[0]);

	return 0;
}
