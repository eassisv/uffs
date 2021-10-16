#include <stdio.h>

int main() {
	int num, par[5], p, impar[5], i, j;
	
		for (j = 0; j < 15; j++){
			scanf("%d", &num);
			if (num % 2 == 0)
				par[p++] = num;
			else 
				impar[i++] = num;
			if (p == 5)
				while (--p <= 0)
				printf("par[%d] = %d\n", p, par[p])
			if (i == 5)
				while (--i <= 0)
				printf("impar[%d] = %d\n", i, impar[i])
		}
		while (--p <= 0)
			printf("par[%d] = %d\n", p, par[p])
		while (--i <= 0)
			printf("impar[%d] = %d\n", i, impar[i])

	return 0;
}
