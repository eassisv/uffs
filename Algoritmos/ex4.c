#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define chr aux[j]

int main(void){
	int leng, i = 0, j, va = 0, v, ind = 0;
	char s[100][100] = {}, aux[100] = {};

	while (fgets(s[i], 100, stdin), s[i][0] != 10){
		leng = strlen(s[i]) - 1;
		v = 0;
		for (j = 0; j < leng; j++){
			aux[j] = tolower(s[i][j]);
			if (chr=='a' ||chr=='e' ||chr=='i' ||chr=='o' ||chr=='u')
				v++;
		}
		if (v >= va){
			va = v;
			ind = i;
		}
		i++;
	}
	printf("%s", s[ind]);
	
	return 0;
}
